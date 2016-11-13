/*
    These are utility function headers that I commonly use in my software.

    Copyright(C) 2016  Michael Brett Koonts

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef UTIL_H_
#define UTIL_H_

#define WINDOWSSYSTEM 1

#if WINDOWSSYSTEM
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif
#include <iostream>
#include <iomanip>
#include <string>
//========================================================================
// REQUIRES: 
// MODIFIES: 
// EFFECTS: 
//========================================================================
#if WINDOWSSYSTEM
void PrintTimeDifference(const FILETIME &start, const FILETIME &end);
#else
void PrintTimeDifference(const timeval &start, const timeval &end);
#endif
//========================================================================
// REQUIRES: 
// MODIFIES: 
// EFFECTS: 
//========================================================================
int calcPercentageComplete(int position, int end);
//========================================================================
// REQUIRES: 
// MODIFIES: 
// EFFECTS: 
//========================================================================
int updateOutputPercentage(int percent, bool finished);
//========================================================================
// REQUIRES: 
// MODIFIES: 
// EFFECTS: 
//========================================================================
void outputStatusMessage(std::string message);

#endif