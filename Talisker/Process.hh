/* Copyright 2015 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef TALISKER_PROCESS_HH_
# define TALISKER_PROCESS_HH_          1

# include <stdarg.h>

# include <Talisker/Object.hh>

namespace Talisker {

	void debug(const char *format, ...);
	void log(const char *format, ...);
	void notice(const char *format, ...);
	void warn(const char *format, ...);
	void err(const char *format, ...);

	class Process: public Object
	{
	public:
		static Process *self();
	public:
		virtual ~Process();

		virtual void debug(const char *format, ...);
		virtual void vdebug(const char *format, va_list ap);
		virtual void log(const char *format, ...);
		virtual void vlog(const char *format, va_list ap);
		virtual void notice(const char *format, ...);
		virtual void vnotice(const char *format, va_list ap);
		virtual void warn(const char *format, ...);
		virtual void vwarn(const char *format, va_list ap);
		virtual void err(const char *format, ...);
		virtual void verr(const char *format, va_list ap);
	protected:
		Process();

		unsigned long m_id;
		int m_argc;
		char **m_argv;
		char **m_envp;
	};

};

#endif /*!TALISKER_PROCESS_HH_*/
