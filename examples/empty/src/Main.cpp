
#include <Siv3D.hpp>

#include "Test2.hpp"


#include <unordered_map>
#include <map>
#include <array>
#include <functional>



inline FilePath GetDir(const FilePath& path)
{
    auto index = String(path).lastIndexOf(L"/");
    return path.substr(0, index + 1);
}


constexpr inline Color NC(const std::unique_ptr<BMS::Note>& note)
{
    switch (note->laneIndex) {
        case 0: return ColorF(0, 0, 0);
        case 1: return ColorF(0, 0, 0);
        case 2: return ColorF(0, 0, 0);
        case 3: return ColorF(0, 0, 0);
        case 4: return ColorF(0, 0, 0);
        case 5: return ColorF(0, 0, 0);
        case 6: return ColorF(0, 0, 0);
        case 7: return ColorF(0, 0, 0);
    }
    return ColorF(0,0,0);
}


inline Array<String> ReadLines(const FilePath& path)
{
    TextReader reader(path);
    Array<String> lines;
    String line;
    while (reader.readLine(line))
    {
        lines.emplace_back(line);
    }
    return lines;
}



class Player
{
    
    Stopwatch m_stopwatch;
    
    Array<BMS::Note> m_notes;
    
    std::unordered_map<int, Audio> m_wavs;
    
    std::array<double, 8> laneSize = { 1.2, 1.0, 0.8, 1.0, 0.8, 1.0, 0.8, 1.0 };
    
    std::array<Color, 8> laneColors = {
        ColorF(0, 0, 0, .8),
        ColorF(1, 1, 1, .3),
        ColorF(0, 0, .5, .8),
        ColorF(1, 1, 1, .3),
        ColorF(0, 0, .5, .8),
        ColorF(1, 1, 1, .3),
        ColorF(0, 0, .5, .8),
        ColorF(1, 1, 1, .3),
    };
    
    
    std::array<Color, 8> colors = {
        Palette::Red,
        Palette::White,
        Palette::Blue,
        Palette::White,
        Palette::Blue,
        Palette::White,
        Palette::Blue,
        Palette::White
    };
    
    
    std::array<std::function<bool()>, 8> keys = {
        []() { return KeyShift.down(); },
        []() { return KeyZ.down(); },
        []() { return KeyS.down(); },
        []() { return KeyX.down(); },
        []() { return KeyD.down(); },
        []() { return KeyC.down(); },
        []() { return KeyF.down(); },
        []() { return KeyV.down(); }
    };
    
    double m_speed = 1.0;
    
    
public:
    
    uint combo = 0;
    
    Player(const FilePath& path)
    {
        
        auto dir = GetDir(path);
        
        auto&& lines = ReadLines(path);
        
        m_notes = BMS::Parser::Parse(lines);
        auto& wavs = BMS::Parser::GetWavs();
        
        std::unordered_map<int, Audio> se;
        
        
        for(auto& wav : wavs)
        {
            
            auto wavPath = dir + wav.second.value;
            
            m_wavs[wav.first] = Audio(wavPath);
            
        }
        
        
        Log << L"WavNum: " << wavs.size();
        
        
        int visibleNoteNum = 0;
        
        for (auto& note : m_notes)
        {
            if (note.visible) ++visibleNoteNum;
        }
        
        Log << Format(L"NoteNum:", m_notes.size());
        Log << Format(L"VNoteNum:", visibleNoteNum);
        
        
        m_stopwatch = Stopwatch(true);
        
        
    }
    
    void update()
    {
        auto sec = m_stopwatch.sF();
        
        
        // ハイスピ変更
        if (KeyUp.down()) m_speed += 0.1;
        if (KeyDown.down()) m_speed -= 0.1;
        
        
        // SE を鳴らす
        for (auto& note : m_notes)
        {
            
            if (note.played) continue;
            
            if (note.time > sec) continue;
            
            m_wavs[note.wavIndex].stop();
            m_wavs[note.wavIndex].play();
            
            note.played = true;
            
        }
        
        
        std::array<Array<BMS::Note *>, 8> sortedNotes;
        
        
        // 判定する
        for (auto &note : m_notes)
        {
            
            if (note.judged) continue;
            
            // キー入力がない
            if (!keys[note.laneIndex]()) return;
            
            auto abs = Math::Abs(note.time - sec);
            
            // ± 0.3 sec
            if (abs < 0.3)
            {
                sortedNotes[note.laneIndex].emplace_back(&note);
            }
            
        }
        
        
        // 判定ラインに近い順でソート
        for (auto& notes : sortedNotes)
        {
            notes.sort_by([sec](BMS::Note*a, BMS::Note*b){
                return Math::Abs(a->time - sec) < Math::Abs(b->time - sec);
            });
        }
        
        
        
        for (auto& notes : sortedNotes)
        {
            
            if (!notes.size()) continue;
            
            
            // 判定する
            auto result = notes[0]->judge(sec);
            
            
            ++combo;
            
        }
        
        
        // 失敗判定
        for (auto& note : m_notes)
        {
            if (note.judged) return;
            if (note.time > sec) return;
            
            // 0.3 秒以上経過している
            if (note.time - sec < -0.3) {
                
                note.judged = true;
                
                combo = 0;
                
            }
            
        }
    
        
        
        
    }
    
    
    
    
    
    
    void render(double x, double y, double w, double h)
    {
        
        const auto rect = RectF(x, y, w, h);
        
        const auto sec = m_stopwatch.sF();
        
        
        // レーンサイズの合計を求める
        double sizeSum = 0.0;
        for (auto& size : laneSize)
        {
            sizeSum += size;
        }
        
        
        auto _x = x;
        
        
        // レーンの座標を求める
        std::array<RectF, 8> laneRects;
        
        for (auto index : step(8))
        {
            
            auto size = laneSize[index] / sizeSum * w;
            
            laneRects[index] = RectF(_x, y, size, h);
            
            _x += size;
            
        }
        
        
        
        // レーンを描画する
        for (auto index : step(8))
        {
            laneRects[index].draw(laneColors[index]);
        }
        
        
        rect.drawFrame(1.0, Palette::Red);
        
        
        // ノーツを描画する
        for (auto& note : m_notes)
        {
            
            if (note.played) continue;
            if (!note.visible) continue;
            
            
            auto position = note.time - sec;
            
            
            
            auto& laneRect = laneRects[note.laneIndex];
            
            
            // 判定ライン
            auto jy = laneRect.y + laneRect.h;
            
            
            auto y = jy - (position * h * m_speed);
            
            
            RectF(laneRect.x, y - 10, laneRect.w, 20).draw(colors[note.laneIndex]);
            
            
            
        }
        
        
        
    }
    
};



void Main()
{
    
    
    String dir = L"../src/Assets/[LV.4] Angel dust/";
    
    Window::Resize(600, 600);
    
    
    Font font(16);
    
    Player player(dir + L"angeldust7_abyss.bme");
    
    
    while (System::Update())
    {
        ClearPrint();
        
        
        auto paths = DragDrop::GetDroppedFilePaths();
        
        if (paths.size())
        {
            player = Player(paths[0].path);
        }
        
        
        player.update();
        player.render(10, 10, 300, 500);
        
        
        Print(player.combo);
        
        
    }
}
