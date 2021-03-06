/*
 * Copyright 2003-2018 The Music Player Daemon Project
 * http://www.musicpd.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "config.h"
#include "Thread.hxx"
#include "thread/Name.hxx"
#include "thread/Slack.hxx"
#include "thread/Util.hxx"
#include "Log.hxx"

void
EventThread::Start()
{
	assert(!thread.IsDefined());

	thread.Start();
}

void
EventThread::Stop() noexcept
{
	if (thread.IsDefined()) {
		event_loop.Break();
		thread.Join();
	}
}

void
EventThread::Run() noexcept
{
	SetThreadName(realtime ? "rtio" : "io");

	if (realtime) {
		SetThreadTimerSlackUS(10);

		try {
			SetThreadRealtime();
		} catch (...) {
			LogError(std::current_exception(),
				 "RTIOThread could not get realtime scheduling, continuing anyway");
		}
	}

	event_loop.Run();
}
