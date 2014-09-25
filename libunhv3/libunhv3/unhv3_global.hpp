/*Copyright (C) 2014  별님

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef UNHV3_GLOBAL_HPP
#define UNHV3_GLOBAL_HPP

#include <QtCore/qglobal.h>

#if defined(UNHV3_LIBRARY)
#  define UNHV3SHARED_EXPORT Q_DECL_EXPORT
#else
#  define UNHV3SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UNHV3_GLOBAL_HPP
