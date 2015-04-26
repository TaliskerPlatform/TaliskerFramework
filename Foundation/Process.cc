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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "p_foundation.hh"

using namespace Talisker;

static int process_argc;
static char **process_argv;
static char **process_envp;
static Process *process;

extern "C" void __attribute__((constructor))
talisker_process_init_(int argc, char **argv, char **envp)
{
	process_argc = argc;
	process_argv = argv;
	process_envp = envp;
}

void
Talisker::debug(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	Process::self()->vdebug(format, ap);
}

void
Talisker::log(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	Process::self()->vlog(format, ap);
}

void
Talisker::notice(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	Process::self()->vnotice(format, ap);
}

void
Talisker::warn(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	Process::self()->vwarn(format, ap);
}

void
Talisker::err(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	Process::self()->verr(format, ap);
}

Process *
Process::self(void)
{
	const char *t;

	if(!process)
	{
		process = new Process();
		process->m_refcount = -1; /* This is a singleton */
		process->m_id = (long) getpid();
		t = strrchr(process_argv[0], '/');
		if(t)
		{
			t++;
		}
		else
		{
			t = process_argv[0];
		}
		openlog(t, LOG_NDELAY|LOG_NOWAIT|LOG_PERROR|LOG_PID, LOG_USER);
		process->m_argc = process_argc;
		process->m_argv = process_argv;
		process->m_envp = process_envp;
	}
	return process;
}

Process::Process():
	Object::Object(),
	m_id(0),
	m_argc(0),
	m_argv(NULL),
	m_envp(NULL)
{
}

Process::~Process()
{
}

void
Process::debug(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vsyslog(LOG_DEBUG, format, ap);
}

void
Process::vdebug(const char *format, va_list ap)
{
	vsyslog(LOG_DEBUG, format, ap);
}

void
Process::log(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vsyslog(LOG_INFO, format, ap);
}

void
Process::vlog(const char *format, va_list ap)
{
	vsyslog(LOG_INFO, format, ap);
}

void
Process::notice(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vsyslog(LOG_NOTICE, format, ap);
}

void
Process::vnotice(const char *format, va_list ap)
{
	vsyslog(LOG_NOTICE, format, ap);
}

void
Process::warn(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vsyslog(LOG_WARNING, format, ap);
}

void
Process::vwarn(const char *format, va_list ap)
{
	vsyslog(LOG_WARNING, format, ap);
}

void
Process::err(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vsyslog(LOG_ERR, format, ap);
}

void
Process::verr(const char *format, va_list ap)
{
	vsyslog(LOG_ERR, format, ap);
}

