﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Platform.hpp"
# include "Types.hpp"

namespace s3d
{
	//////////////////////////////////////////////////////
	//
	//	Uncopyable.hpp
	//
	class Uncopyable;

	//////////////////////////////////////////////////////
	//
	//	ConcurrentTask.hpp
	//
	template <class Type> class ConcurrentTask;

	//////////////////////////////////////////////////////
	//
	//	AlignedAllocator.hpp
	//
	template <class Type, size_t Alignment> class AlignedAllocator;
	template <class Type> struct DefaultAllocator;

	//////////////////////////////////////////////////////
	//
	//	Array.hpp
	//
	template <class Type, class Allocator> class Array;

	//////////////////////////////////////////////////////
	//
	//	Byte.hpp
	//
	enum class Byte : unsigned char;

	//////////////////////////////////////////////////////
	//
	//	ByteArrayView.hpp
	//
	class ByteArrayView;

	//////////////////////////////////////////////////////
	//
	//	Grid.hpp
	//
	template <class Type, class Allocator> class Grid;

	//////////////////////////////////////////////////////
	//
	//	Optional.hpp
	//
	struct None_t;
	template <class Type> class Optional;

	//////////////////////////////////////////////////////
	//
	//	IteratorRange.hpp
	//
	template <class IteratorType> class IteratorRange;

	//////////////////////////////////////////////////////
	//
	//	String.hpp
	//
	class String;
	using FilePath = String;

	//////////////////////////////////////////////////////
	//
	//	StringView.hpp
	//
	template <class CharType> class BasicStringView;
	using CStringView		= BasicStringView<char>;
	using UTF8StringView	= BasicStringView<char>;
	using StringView		= BasicStringView<wchar>;

	//////////////////////////////////////////////////////
	//
	//	LetterCase.hpp
	//
	enum class LetterCase;

	//////////////////////////////////////////////////////
	//
	//	BigInt.hpp
	//
	class BigInt;

	//////////////////////////////////////////////////////
	//
	//	BigFloat.hpp
	//
	class BigFloat;

	//////////////////////////////////////////////////////
	//
	//	Format.hpp
	//
	struct FormatData;

	//////////////////////////////////////////////////////
	//
	//	Date.hpp
	//
	struct Date;

	//////////////////////////////////////////////////////
	//
	//	DateTime.hpp
	//
	struct DateTime;

	//////////////////////////////////////////////////////
	//
	//	Stopwatch.hpp
	//
	class Stopwatch;

	//////////////////////////////////////////////////////
	//
	//	SpeedStopwatch.hpp
	//
	class SpeedStopwatch;

	//////////////////////////////////////////////////////
	//
	//	Timer.hpp
	//
	class Timer;

	//////////////////////////////////////////////////////
	//
	//	TimeProfiler.hpp
	//
	class TimeProfiler;

	//////////////////////////////////////////////////////
	//
	//	RDTSCClock.hpp
	//
	class RDTSCClock;

	//////////////////////////////////////////////////////
	//
	//	FileSystem.hpp
	//
	enum class OpenMode;
	enum class CopyOption;
	enum class SpecialFolder;

	//////////////////////////////////////////////////////
	//
	//	IReader.hpp
	//
	class IReader;

	//////////////////////////////////////////////////////
	//
	//	IWriter.hpp
	//
	class IWriter;

	//////////////////////////////////////////////////////
	//
	//	ReaderView.hpp
	//
	class ReaderView;

	//////////////////////////////////////////////////////
	//
	//	MemoryMapping.hpp
	//
	class MemoryMapping;

	//////////////////////////////////////////////////////
	//
	//	WritableMemoryMapping.hpp
	//
	class WritableMemoryMapping;
	enum class MMFOpenMode_if_Exists;
	enum class MMFOpenMode_if_NotFound;

	//////////////////////////////////////////////////////
	//
	//	ByteArray.hpp
	//
	class ByteArray;

	//////////////////////////////////////////////////////
	//
	//	MemoryWriter.hpp
	//
	class MemoryWriter;

	//////////////////////////////////////////////////////
	//
	//	BinaryReader.hpp
	//
	class BinaryReader;

	//////////////////////////////////////////////////////
	//
	//	BinaryWriter.hpp
	//
	class BinaryWriter;

	//////////////////////////////////////////////////////
	//
	//	CharacterEncoding.hpp
	//
	enum class CharacterEncoding;

	//////////////////////////////////////////////////////
	//
	//	TextReader.hpp
	//
	class TextReader;

	//////////////////////////////////////////////////////
	//
	//	TextWriter.hpp
	//
	class TextWriter;

	//////////////////////////////////////////////////////
	//
	//	MD5.hpp
	//
	struct MD5Hash;

	//////////////////////////////////////////////////////
	//
	//	Logger.hpp
	//
	enum class OutputLevel;
	enum class LogDescription;




	//////////////////////////////////////////////////////
	//
	//	INIReader.hpp
	//
	struct INIKey;
	class INIReader;



	//////////////////////////////////////////////////////
	//
	//	JSONReader.hpp
	//
	enum class JSONValueType;
	class JSONArrayIterator;
	class JSONObjectIterator;
	class JSONArrayView;
	class JSONObjectView;
	class JSONValue;
	struct JSONObjectMember;
	class JSONReader;



	//////////////////////////////////////////////////////
	//
	//	Color.hpp
	//
	struct Color;
	struct ColorF;

	//////////////////////////////////////////////////////
	//
	//	HSV.hpp
	//
	struct HSV;

	//////////////////////////////////////////////////////
	//
	//	PointVector.hpp
	//
	struct Point;
	using Size = Point;
	template <class Type> struct Vector2D;
	template <class Type> struct Vector3D;
	template <class Type> struct Vector4D;
	using Float2	= Vector2D<float>;
	using Vec2		= Vector2D<double>;
	using Float3	= Vector3D<float>;
	using Vec3		= Vector3D<double>;
	using Float4	= Vector4D<float>;
	using Vec4		= Vector4D<double>;

	//////////////////////////////////////////////////////
	//
	//	Circular.hpp
	//
	template <int32 Oclock> struct CircularBase;
	using Circular	= CircularBase<0>;
	using Circular0	= CircularBase<0>;
	using Circular3	= CircularBase<3>;
	using Circular6	= CircularBase<6>;
	using Circular9	= CircularBase<9>;

	//////////////////////////////////////////////////////
	//
	//	Cylindrical.hpp
	//
	struct Cylindrical;

	//////////////////////////////////////////////////////
	//
	//	Spherical.hpp
	//
	struct Spherical;

	//////////////////////////////////////////////////////
	//
	//	Mat3x2.hpp
	//
	struct Mat3x2;

	//////////////////////////////////////////////////////
	//
	//	Line.hpp
	//
	struct LineStyle;
	struct Line;

	//////////////////////////////////////////////////////
	//
	//	Rectangle.hpp
	//
	template <class SizeType> struct Rectangle;
	using Rect = Rectangle<Point>;
	using RectF = Rectangle<Vec2>;

	//////////////////////////////////////////////////////
	//
	//	Circle.hpp
	//
	struct Circle;

	//////////////////////////////////////////////////////
	//
	//	Ellipse.hpp
	//
	struct Ellipse;

	//////////////////////////////////////////////////////
	//
	//	Triangle.hpp
	//
	struct Triangle;

	//////////////////////////////////////////////////////
	//
	//	Quad.hpp
	//
	struct Quad;

	//////////////////////////////////////////////////////
	//
	//	RoundRect.hpp
	//
	struct RoundRect;

	//////////////////////////////////////////////////////
	//
	//	LineString.hpp
	//
	class LineString;

	//////////////////////////////////////////////////////
	//
	//	Polygon.hpp
	//
	class Polygon;

	//////////////////////////////////////////////////////
	//
	//	MultiPolygon.hpp
	//
	class MultiPolygon;

	//////////////////////////////////////////////////////
	//
	//	FloatRect.hpp
	//
	struct FloatRect;

	//////////////////////////////////////////////////////
	//
	//	FloatQuad.hpp
	//
	struct FloatQuad;

	//////////////////////////////////////////////////////
	//
	//	Shape2D.hpp
	//
	class Shape2D;


	//////////////////////////////////////////////////////
	//
	//	Distribution.hpp
	//
	template <class Type> class UniformDistribution;
	template <class Type> class NormalDistribution;

	//////////////////////////////////////////////////////
	//
	//	HardwareRNG.hpp
	//
	class HardwareRNG;

	//////////////////////////////////////////////////////
	//
	//	Xorshift.hpp
	//
	class Xorshift64Star;
	class Xorshift128Plus;
	class Xorshift1024Star;

	//////////////////////////////////////////////////////
	//
	//	MersenneTwister.hpp
	//
	class MT11213b;
	class MT19937;
	class MT19937_64;

	//////////////////////////////////////////////////////
	//
	//	DefaultRNG.hpp
	//
	using DefaultRNGType = MT11213b;

	//////////////////////////////////////////////////////
	//
	//	EasingController.hpp
	//
	template <class Type> class EasingController;

	//////////////////////////////////////////////////////
	//
	//	Transition.hpp
	//
	class Transition;

	//////////////////////////////////////////////////////
	//
	//	PerlinNoise.hpp
	//
	class PerlinNoise;

	//////////////////////////////////////////////////////
	//
	//	Bezier2.hpp
	//
	struct Bezier2;
	struct Bezier2Path;

	//////////////////////////////////////////////////////
	//
	//	Bezier3.hpp
	//
	struct Bezier3;
	struct Bezier3Path;

	//////////////////////////////////////////////////////
	//
	//	HalfFloat.hpp
	//
	struct HalfFloat;

	//////////////////////////////////////////////////////
	//
	//	MathParser.hpp
	//
	class MathParser;



	//////////////////////////////////////////////////////
	//
	//	Image.hpp
	//
	class Image;

	//////////////////////////////////////////////////////
	//
	//	ImageFormat.hpp
	//
	enum class ImageFormat;
	enum class PPMType;
	class IImageFormat;

	//////////////////////////////////////////////////////
	//
	//	TextureFormat.hpp
	//
	enum class TextureFormat;



	//////////////////////////////////////////////////////
	//
	//	WaveSample.hpp
	//
	struct WaveSampleS16;
	struct WaveSample;

	//////////////////////////////////////////////////////
	//
	//	Wave.hpp
	//
	class Wave;

	//////////////////////////////////////////////////////
	//
	//	AudioFormat.hpp
	//
	enum class AudioFormat;
	enum class WAVEFormat;
	class IAudioFormat;

	//////////////////////////////////////////////////////
	//
	//	CPU.hpp
	//
	enum class CPUVendor;
	struct CPUFeature;

	//////////////////////////////////////////////////////
	//
	//	Monitor.hpp
	//
	struct Monitor;

	//////////////////////////////////////////////////////
	//
	//	Window.hpp
	//
	enum class ShowState;
	struct WindowState;

	//////////////////////////////////////////////////////
	//
	//	MessageBox.hpp
	//
	enum class MessageBoxStyle;
	enum class MessageBoxButtons;
	enum class MessageBoxSelection;

	//////////////////////////////////////////////////////
	//
	//	DragDrop.hpp
	//
	enum class DragItemType;
	struct DragStatus;
	struct DroppedFilePath;
	struct DroppedText;

	//////////////////////////////////////////////////////
	//
	//	PowerStatus.hpp
	//
	enum class ACLineStatus;
	enum class BatteryStatus;
	struct PowerStatus;

	//////////////////////////////////////////////////////
	//
	//	AssetHandle.hpp
	//
	template <class Type> class AssetHandle;

	//////////////////////////////////////////////////////
	//
	//	Cursor.hpp
	//
	enum class CursorStyle;

	//////////////////////////////////////////////////////
	//
	//	Key.hpp
	//
	enum class InputDevice : uint8;
	class Key;

	//////////////////////////////////////////////////////
	//
	//	KeyConjunction.hpp
	//
	class KeyConjunction;

	//////////////////////////////////////////////////////
	//
	//	KeyGroup.hpp
	//
	class KeyGroup;

	//////////////////////////////////////////////////////
	//
	//	TextInput.hpp
	//
	enum class TextInputMode;



	//////////////////////////////////////////////////////
	//
	//	Audio.hpp
	//
	class Audio;


	//////////////////////////////////////////////////////
	//
	//	Vertex2D.hpp
	//
	struct Vertex2D;

	//////////////////////////////////////////////////////
	//
	//	Sprite.hpp
	//
	struct Sprite;

	//////////////////////////////////////////////////////
	//
	//	BlendState.hpp
	//
	enum class Blend : uint8;
	enum class BlendOp : uint8;
	struct BlendState;

	//////////////////////////////////////////////////////
	//
	//	RasterizerState.hpp
	//
	enum class FillMode : uint8;
	enum class CullMode : uint8;
	struct RasterizerState;

	//////////////////////////////////////////////////////
	//
	//	SamplerState.hpp
	//
	enum class TextureFilter : bool;
	enum class TextureAddressMode : uint8;
	struct SamplerState;
	
	//////////////////////////////////////////////////////
	//
	//	RenderStateBlock2D.hpp
	//
	class RenderStateBlock2D;

	//////////////////////////////////////////////////////
	//
	//	ViewportBlock2D.hpp
	//
	class ViewportBlock2D;
	
	//////////////////////////////////////////////////////
	//
	//	Transformer2D.hpp
	//
	class Transformer2D;
	
	//////////////////////////////////////////////////////
	//
	//	Shader.hpp
	//
	enum class ShaderStage;
	struct BindingPoint;

	//////////////////////////////////////////////////////
	//
	//	VertexShader.hpp
	//
	class VertexShader;

	//////////////////////////////////////////////////////
	//
	//	PixelShader.hpp
	//
	class PixelShader;

	//////////////////////////////////////////////////////
	//
	//	ConstantBuffer.hpp
	//
	template <class Type> class ConstantBuffer;

	//////////////////////////////////////////////////////
	//
	//	Graphics.hpp
	//
	struct DisplayMode;
	struct DisplayOutput;


	//////////////////////////////////////////////////////
	//
	//	Texture.hpp
	//
	enum class TextureDesc;
	class Texture;

	//////////////////////////////////////////////////////
	//
	//	TextureRegion.hpp
	//
	struct TextureRegion;

	//////////////////////////////////////////////////////
	//
	//	TexturedCircle.hpp
	//
	struct TexturedCircle;

	//////////////////////////////////////////////////////
	//
	//	TexturedQuad.hpp
	//
	struct TexturedQuad;

	//////////////////////////////////////////////////////
	//
	//	TexturedRoundRect.hpp
	//
	struct TexturedRoundRect;

	//////////////////////////////////////////////////////
	//
	//	DynamicTexture.hpp
	//
	class DynamicTexture;

	//////////////////////////////////////////////////////
	//
	//	RenderTexture.hpp
	//
	class RenderTexture;

	//////////////////////////////////////////////////////
	//
	//	Font.hpp
	//
	enum class Typeface;
	enum class FontStyle : uint32;
	struct Glyph;
	class Font;
	class GlyphIterator;
	struct DrawableText;

	//////////////////////////////////////////////////////
	//
	//	Emoji.hpp
	//
	struct Emoji;

	//////////////////////////////////////////////////////
	//
	//	Icon.hpp
	//
	struct Icon;

	//////////////////////////////////////////////////////
	//
	//	TextBox.hpp
	//
	class TextBox;

	//////////////////////////////////////////////////////
	//
	//	Effect.hpp
	//
	struct IEffect;
	class Effect;
}