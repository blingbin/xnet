#ifndef _XNET_COMMON_LOGGING_H_
#define _XNET_COMMON_LOGGING_H_

#include "LogStream.h"
#include "Timestamp.h"

namespace xnet
{
	class Logger
	{
	public:
		enum LogLevel
		{
			TRACE, DEBUG, INFO, WARN, ERROR, FATAL, NUM_LOG_LEVELS,
		};

		// compile time calculation of basename of source file
		class SourceFile
		{
		public:
			template<int N>
			inline SourceFile(const char (&arr)[N]) :
					data_(arr), size_(N - 1)
			{
				const char* slash = strrchr(data_, '/'); // builtin function
				if (slash)
				{
					data_ = slash + 1;
					size_ -= static_cast<int>(data_ - arr);
				}
			}

			explicit SourceFile(const char* filename) :
					data_(filename)
			{
				const char* slash = strrchr(filename, '/');
				if (slash)
				{
					data_ = slash + 1;
				}
				size_ = static_cast<int>(strlen(data_));
			}

			const char* data_;
			int size_;
		};

		Logger(SourceFile file, int line);
		Logger(SourceFile file, int line, LogLevel level);
		Logger(SourceFile file, int line, LogLevel level, const char* func);
		Logger(SourceFile file, int line, bool toAbort);
		~Logger();

		LogStream& stream()
		{
			return impl_.stream_;
		}

		static LogLevel logLevel();
		static void setLogLevel(LogLevel level);

		typedef void (*OutputFunc)(const char* msg, int len);
		typedef void (*FlushFunc)();
		static void setOutput(OutputFunc);
		static void setFlush(FlushFunc);

	private:

		class Impl
		{
		public:
			typedef Logger::LogLevel LogLevel;
			Impl(LogLevel level, int old_errno, const SourceFile& file, int line);
			void formatTime();
			void finish();

			Timestamp time_;
			LogStream stream_;
			LogLevel level_;
			int line_;
			SourceFile basename_;
		};

		Impl impl_;

	};

	extern Logger::LogLevel g_logLevel;

	inline Logger::LogLevel Logger::logLevel()
	{
		return g_logLevel;
	}

#define LOG_TRACE if (xnet::Logger::logLevel() <= xnet::Logger::TRACE) \
  xnet::Logger(__FILE__, __LINE__, xnet::Logger::TRACE, __func__).stream()
#define LOG_DEBUG if (xnet::Logger::logLevel() <= xnet::Logger::DEBUG) \
  xnet::Logger(__FILE__, __LINE__, xnet::Logger::DEBUG, __func__).stream()
#define LOG_INFO if (xnet::Logger::logLevel() <= xnet::Logger::INFO) \
  xnet::Logger(__FILE__, __LINE__).stream()
#define LOG_WARN xnet::Logger(__FILE__, __LINE__, xnet::Logger::WARN).stream()
#define LOG_ERROR xnet::Logger(__FILE__, __LINE__, xnet::Logger::ERROR).stream()
#define LOG_FATAL xnet::Logger(__FILE__, __LINE__, xnet::Logger::FATAL).stream()
#define LOG_SYSERR xnet::Logger(__FILE__, __LINE__, false).stream()
#define LOG_SYSFATAL xnet::Logger(__FILE__, __LINE__, true).stream()

	const char* strerror_tl(int savedErrno);

// Taken from glog/logging.h
//
// Check that the input is non NULL.  This very useful in constructor
// initializer lists.

#define CHECK_NOTNULL(val) \
  ::xnet::CheckNotNull(__FILE__, __LINE__, "'" #val "' Must be non NULL", (val))

// A small helper for CHECK_NOTNULL().
	template<typename T>
	T* CheckNotNull(Logger::SourceFile file, int line, const char *names, T* ptr)
	{
		if (ptr == NULL)
		{
			Logger(file, line, Logger::FATAL).stream() << names;
		}
		return ptr;
	}

}

#endif  // _XNET_COMMON_LOGGING_H_
