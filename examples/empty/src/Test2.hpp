#ifndef Test2_hpp
#define Test2_hpp

#include <Siv3D.hpp>

#include <unordered_map>
#include <array>

#include "Header.hpp"


#include <memory>

namespace BMS
{
    
    enum class JudgeResult
    {
        
    };
    
    struct Note
    {
        float time;
        
        // TODO: int to uint8
        int laneIndex;
        int wavIndex;
        
        
        
        
        bool visible = false;
        
        
        bool played = false;
        
        bool judged = false;
        
        
        uint8 judge(const double sec)
        {
            
            
            this->judged = true;
            
            auto r = Math::Abs(time - sec);
            
            if (r >= 0.2) return 1;
            if (r >= 0.1) return 2;
            if (r >= 0.0) return 3;
            
        
            
            return 0;
        }
        
    };
    
}





namespace BMS::Parser
{
    
    // using bms_id = int;
    
    enum class T
    {
        A = 0,
        B = 1,
    };
    
    
    std::array<String, 2> splitTokens(String source)
    {
        
        // auto split = source.split(L' ');
        
        std::array<String, 2> results;
        
        
        auto space = source.indexOf(L" ");
        
        results[0] = source.substr(0, space - 1);
        results[1] = source.substr(space).trim();
        
        
        return results;
    }
    
    
    
    class BMS_Header
    {
    public:
        String name;
        int id;
        String value;
        
        int intValue() const
        {
            return ParseInt<int>(value, Arg::radix = 10);
        }
        
        float floatValue()const
        {
            return ParseFloat<float>(value);
        }
        
        
        BMS_Header()
        {
            
        }
        
        BMS_Header(String source)
        {
            
            auto tokens = splitTokens(source);
            
            name = tokens[0];
            
            value = tokens[1];
            
            
        }
        
        
        
        BMS_Header(String source, int n)
        {
            
            auto tokens = splitTokens(source);
            
            name = tokens[0];
            value = tokens[1];
            
            
            id = ParseInt<int>(name.substr(name.length() - 2), Arg::radix = n);
            
            
        }
        
    };
    
    
    
    
    
    std::unordered_map<int, BMS_Header> HeaderCollection_BPM;
    std::unordered_map<int, BMS_Header> HeaderCollection_WAV;
    std::unordered_map<int, BMS_Header> HeaderCollection_STOP;
    
    
    
    
    String header(const String& source)
    {
        auto tokens = splitTokens(source);
        return tokens[1];
    }
    
    
    
    
    
    struct NotePosition
    {
        
        // [[x]] / y
        int numerator;
        
        // x / [[y]]
        int denominator;
        
        NotePosition() { }
        
        NotePosition(int numerator, int denominator)
        {
            this->numerator = numerator;
            this->denominator = denominator;
        }
        
        double value() const
        {
            return 1.0 / denominator * numerator;
        }
        
    };
    
    
    class Note
    {
    public:
        
        
        // bool judged = false;
        
        
        float __time;
        int id = -1;
        int se;
        
        NotePosition position;
        
        double getCompPos()
        {
            return laneIndex + position.value();
        }
        
        float time;
        
        int laneIndex = -1;
        
        
        Note(float __time, int se)
        {
            
            
            this->__time = __time;
            this->se = se;
            
            
            if (se != 0)
            {
                
                
                // LoadFile file = hm2.get(se);
                //
                //if (file != null)
                // {
                //
                // file.enabled = true;
                
                //  }
                
            }
            
            
        }
        
        
    };
    
    
    Array<std::unique_ptr<Note>> notes;
    
    
    
    void note(int index, int id, const String& values)
    {
        
        auto mc = Regex::Search(values, LR"(.{2})");
        
        // auto mc = Regex.Matches(values, @".{2}", RegexOptions.ECMAScript);
        
        auto& matches = mc;
        
        auto ln = mc.count();
        int count = 0;
        
        for (auto& c : mc)
        {
            
            // HACK
            // b = c.Value();
            auto b = c.str();
            
            int index2 = count++;
            
            
            if (b.length() == 0) continue;
            
            
            
            // xxxXX:[[11223344]]
            
            int value = ParseInt<int>(b, Arg::radix = 36);
            
            // 休符
            
            if (value == 0) continue;
            
            int soundID = value;
            
            
            auto note = std::make_unique<Note>(-1, soundID);
            
            
            note->laneIndex = index;
            
            note->position =  NotePosition(index2, (int)ln);
            
            
            note->id = -1;
            if (id == 16) note->id = 0;
            if (id == 11) note->id = 1;
            if (id == 12) note->id = 2;
            if (id == 13) note->id = 3;
            if (id == 14) note->id = 4;
            if (id == 15) note->id = 5;
            if (id == 18) note->id = 6;
            if (id == 19) note->id = 7;
            
            // フリースクラッチ
            // if (id == 17) note.id = 0;
            
            
            notes.push_back(std::move(note));
            
        }
        
        
        
    }
    
    
    class BMS_Object
    {
        
        
    public:
        int laneIndex = -1;
        
        NotePosition position;
        
        
        float time;
        
        
        float getCompPos()
        {
            return laneIndex + position.value();
        }
        
        
    };
    
    //   class BPM;
    
    
    
    class BPM : public BMS_Object
    {
    public:
        
        double value = 120.0;
        
        BPM()
        {
            // BPM::collection.Add(*this);
        }
        
    };
    
    Array<BPM> bpms;
    
    
    
    
    
    
    // Array<BPM> BPM::collection;
    
    
    
    
    // class Stop;
    
    //  Array<Stop>StopCollection;
    
    
    class Stop :public BMS_Object
    {
        
    public:
        int value = 0;
        
        // 停止時の BPM
        
        float bpm;
        
        
        Stop()
        {
            //      StopCollection.Add(*this);
        }
        
    };
    
    
    Array<Stop> StopCollection;
    
    
    void addStop(int laneIndex, const String& source)
    {
        
        
        auto values = Regex::Search(source, LR"(.{2})");
        
        //        auto values = Regex.Matches(source, @".{2}");
        
        
        
        
        
        int denominator = (int)values.count();
        int count = 0;
        
        
        
        
        for (auto& value : values)
        {
            
            int index = count++;
            
            
            if (value.length() == 0) continue;
            
            // 00 ~ FF
            
            // int bpm = RadixConvert.ToInt32(value.Value[0].ToString(), 36);
            
            int bpm = ParseInt<int>(String(1, value.str().at(0)), Arg::radix = 36);
            
            if (bpm == 0) continue;
            
            
            Stop bpmObj;// = new Stop();
            
            bpmObj.laneIndex = laneIndex;
            bpmObj.position =  NotePosition(index, denominator);
            
            
            
            // BPM が存在しない
            if(! HeaderCollection_STOP.count(bpm))
            {
                
                StopCollection.emplace_back(bpmObj);
                return;
            }
            
            bpmObj.value = HeaderCollection_STOP[bpm].intValue();
            
            StopCollection.emplace_back(bpmObj);
        }
        
    }
    
    void bpmN(int laneIndex, String source)
    {
        
        auto values = Regex::Search(source, L".{2}");
        
        int denominator = (int)values.count();
        
        int count = 0;
        
        
        for (auto& value : values)
        {
            
            int index = count++;
            
            
            if (value.str().length() == 0) continue;
            
            
            // 00 ~ FF
            int bpm = ParseInt<int>(String(1, value.str().at(0)), Arg::radix = 16);
            // int bpm = Convert.ToInt32(value.Value[0].ToString(), 16);
            
            if (bpm == 0) continue;
            
            
            BPM bpmObj ;
            
            bpmObj.laneIndex = laneIndex;
            bpmObj.position =  NotePosition(index, denominator);
            
            bpmObj.value = (float)(bpm);
            
            bpms.emplace_back(bpmObj);
            
            
        }
        
    }
    
    
    void bpmEx(int laneIndex, String source)
    {
        
        auto values = Regex::Search(source, L".{2}");
        
        
        int denominator = (int)values.count();
        int count = 0;
        
        
        for (auto& value : values)
        {
            
            int index = count++;
            
            
            if (value.str().length() == 0) continue;
            
            // 00 ~ FF
            
            int bpmIndex = ParseInt<int>(String(1, value.str().at(0)), Arg::radix = 16);
            
            if (bpmIndex == 0) continue;
            
            
            BPM bpmObj ;
            
            
            bpmObj.laneIndex = laneIndex;
            bpmObj.position =  NotePosition(index, denominator);
            
            
            // println(bpmIndex.ToString());
            
            bpmObj.value = HeaderCollection_BPM[bpmIndex].floatValue();
            
            
            bpms.emplace_back(bpmObj);
            
        }
        
    }
    
    
    
    
    
    
    
    float bpm = 120.f;
    float defaultBPM = 120.f;
    
    class Lane
    {
    public:
        
        float tempo = 1.0f;
        
        
        // レーンの開始時間
        float beginTime = 0;
        
        
        
        Lane()
        :tempo(1.f),beginTime(0.f)
        {
            
            //LaneCollection.Add(this);
        }
        
    };
    
    
    Array<std::unique_ptr<Lane>> lanes;
    
    
    class Tempo
    {
        
    public:
        
        int laneIndex;
        float value;
        
        Tempo(int laneIndex, float value)
        {
            this->laneIndex = laneIndex;
            this->value = value;
            //  TempoCollection.Add(*this);
        }
    };
    
    
    Array<Tempo> TempoCollection;// = new List<Tempo>();
    
    
    
    
    void channel(int index, int id, const String& values)
    {
        
        int laneIndex = index;
        
        
        // 拡張 BPM
        if (id == 8)
        {
            
            bpmEx(laneIndex, values);
            
            return;
        }
        
        
        if (id == 9)
        {
            
            addStop(laneIndex, values);
            
            
            return;
        }
        
        // xxx02: tempo
        if (id == 2)
        {
            
            // values には 0.125 みたいな文字列が入っている
            auto value = ParseFloat<double>(values);
            
            Tempo tempo(laneIndex, value);
            
            TempoCollection.emplace_back(tempo);
            
            return;
        }
        
        // xxx03: BPM
        if (id == 3)
        {
            
            bpmN(laneIndex, values);
            
            return;
        }
        
        
        
        // 自動再生ノーツ
        if (id == 1)
        {
            
            note(index, id, values);
            return;
        }
        
        
        // ノーツ
        if (11 <= id && id <= 19)
        {
            
            note(index, id, values);
            
            
            return;
        }
        
        
        
        
    }
    
    
    class Minim { };
    
    Minim minim;
    
    
    
    String headerN(String source)
    {
        
        auto tokens = splitTokens(source);
        
        return tokens[1];
        
    }
    
    
    
    bool IsMatch(const String& source, const String& regex)
    {
        return Regex::Search(source, regex).count();
    }
    
    
    Array<BMS::Note> Parse(const Array<String>& lines)
    {
        
        
        
        
        // レーン数を算出する
        int laneLength = -1;
        
        for (auto& line : lines)
        {
            
            if (!IsMatch(line, LR"(#\d{3}[0-9A-Z]{2}:.+)")) continue;
            
            
            int laneIndex = ParseInt<int>(line.substr(1, 3), Arg::radix = 10);
            
            
            laneLength = Max(laneLength, laneIndex);
            
        }
        
        
        // laneLength の値は最大のインデックスなので、 laneLength + 1 確保する
        laneLength += 1;
        
        
        Log << Format(L"レーン数: ", laneLength);
        
        
        //Debug.LogWarning("Lane Length: " + laneLength);
        
        String wavs = L"";
        
        
        for (auto& line : lines)
        {
            
            // Debug.Log(line);
            
            try
            {
                
                
                if (IsMatch(line, LR"(#\d{3}[0-9A-Z]{2}:.+)"))
                {
                    
                    auto index = ParseInt<int>(line.substr(1, 3), Arg::radix = 10);
                    auto id = ParseInt<int>(line.substr(4, 2), Arg::radix = 10);
                    auto values = line.substr(7);
                    
                    // Log << line << L"||" << index << L"|" << id << L"|" << values;
                    
                    channel(index, id, values.trim());
                    
                    continue;
                }
                
                if (IsMatch(line,  LR"(#WAV[0-9A-Z]{2} .+)"))
                {
                    
                    
                    auto s = splitTokens(line);         // トークンで分割
                    
                    //
                    auto id_36 = line.substr(4, 2);
                    
                    int id = ParseInt<int>(line.substr(4, 2), Arg::radix = 36);
                    
                    
                    wavs += L"" + ToString(id) + L":" + s[1] + L"\n";
                    
                    BMS_Header header;//= new BMS_Header();
                    
                    header.value = s[1];
                    
                    HeaderCollection_WAV[id] = header;
                    
                    continue;
                }
                
                if (IsMatch(line, LR"(#BPM .+)"))
                {
                    bpm = ParseFloat<double>(line.substr(5));
                    defaultBPM = bpm;
                    continue;
                }
                
                if (IsMatch(line, LR"(#BPM[0-9A-F]{2} .+)"))
                {
                    
                    
                    
                    float bpm = ParseFloat<double>(headerN(line));
                    
                    //println(bpm.ToString());
                    
                    BMS_Header header(line, 16);// = new BMS_Header(line, 16);
                    
                    HeaderCollection_BPM[header.id] = header;//.Add(header.id, header);
                    
                    
                    continue;
                }
                
                if (IsMatch(line, LR"(#STOP[0-9A-Z]{2} .+)"))
                {
                    
                    BMS_Header header(line, 36);
                    
                    int stop = header.intValue();
                    
                    //  println("Stop", header.id.ToString(), stop.ToString());
                    
                    
                    HeaderCollection_STOP[header.id] = header;//.Add(header.id, header);
                    
                    continue;
                }
                
                
                
            }
            catch (...)
            {
                Log << L"Error";
                //     Debug.LogError(e.Message + ", " + e.StackTrace);
            }
        }
        
        
        
        
        for (auto _ : step(laneLength))
        {
            
            auto lane = std::make_unique<Lane>();
            
            lanes.push_back(std::move(lane));
            
        }
        
        
        
        
        for (auto& tempo : TempoCollection)
        {
            
            continue;
            
            auto& lane = lanes[tempo.laneIndex];
            
            lane->tempo = tempo.value;
            
            
        }
        
        
        // レーンの開始時間を算出する
        float beginTime2 = 0.0f;
        
        int n = 0;
        
        for (auto& lane : lanes)
        {
            
            lane->beginTime = beginTime2;
            
            beginTime2 += lane->tempo;
            
            
            
            // Log << Format(L"lane ", n, L" beginTime: ", lane->beginTime);
            
            ++n;
        }
        
        
        
        int maxLaneLength = 0;
        
        for (auto& note : notes)
        {
            maxLaneLength = Max(maxLaneLength, note->laneIndex);
        }
        
        
        
        for (auto& note : notes)
        {
            
            
            
            
            auto& lane = lanes[note->laneIndex];
            
            float tempo = lane->tempo;
            
            
            float time = lane->beginTime;
            
            
            
            time += tempo / note->position.denominator * note->position.numerator;
            
            
            
            // Log << time;
            
            note->time = time;
            
            
            
        }
        
        
        
        for (auto& note : bpms)
        {
            
            
            continue;
            
            auto& lane = lanes[note.laneIndex];
            
            float tempo = lane->tempo;
            float time = lane->beginTime;
            
            time += tempo / note.position.denominator * note.position.numerator;
            
            
            note.time = time;
            
        }
        
        
        
        /*
         foreach (Note note in notes)
         {
         
         // println(note.time);
         }
         */
        
        
        
        // Stop BPM の初期化
        for (auto& stop : StopCollection)
        {
            stop.bpm = defaultBPM;
        }
        
        
        
        // BPM を適用する
        
        
        
        float beginPos = 0.0f;
        
        float bBPM = defaultBPM;
        
        
        for (auto& bpm : bpms)
        {
            
            
            continue;
            
            // println("--BPM", bpm.value);
            
            
            float pos = bpm.getCompPos();
            
            
            // 譜面停止に BPM を割り当てる
            for (auto& stop : StopCollection)
            {
                if (pos <= (stop.getCompPos()))
                {
                    
                    stop.bpm = bpm.value;
                    
                }
                
            }
            
            for (auto &note : notes)
            {
                if (pos <= (note->getCompPos()))
                {
                    
                    // println("BPMOver", note.getCompPos());
                    
                    //println(bpm.value, note.laneIndex);
                    
                    //float c = a - b;
                    
                    note->time -= bpm.time;
                    // println("Sub", note.time);
                    note->time *= (bBPM / bpm.value);
                    
                    note->time += bpm.time;
                    
                    
                }
            }
            
            
            for (auto& note : bpms)
            {
                if (pos < (note.getCompPos()))
                {
                    
                    // println("BPMOver", note.getCompPos());
                    
                    //println(bpm.value, note.laneIndex);
                    
                    //float c = a - b;
                    
                    note.time -= bpm.time;
                    // println("Sub", note.time);
                    note.time *= (bBPM / bpm.value);
                    
                    note.time += bpm.time;
                    
                    
                }
            }
            
            
            
            
            beginPos = bpm.getCompPos();
            bBPM = bpm.value;
            
        }
        
        
        
        
        for (auto& note : notes)
        {
            
            note->time = note->time * (60.0 / defaultBPM * 4.0);
            
        }
        
        
        
        
        // 譜面停止の計算
        for (auto& stop : StopCollection)
        {
            
            
            continue;
            
            
            for (auto& note : notes)
            {
                if (stop.getCompPos() < (note->getCompPos()))
                {
                    
                    // 1 / (bpm / value * 0.8)
                    note->time += 1.0 / (stop.bpm / stop.value * 0.8);
                    
                    
                }
            }
        }
        
        
        Array<BMS::Note> resultNotes;
        
        
        for (auto& note : notes)
        {
            
            
            BMS::Note resultNote;
            
            resultNote.time = note->time;
            resultNote.laneIndex = note->id;
            resultNote.wavIndex = note->se;
            
            resultNote.visible = note->id != -1;
            
            
            resultNotes.emplace_back(resultNote);
            
        }
        
        
        Log << L"DefaultBPM: " << defaultBPM;
        
        return resultNotes;
        
    }
    
    
    auto& GetWavs()
    {
        return HeaderCollection_WAV;
    }
    
    
}

#endif
