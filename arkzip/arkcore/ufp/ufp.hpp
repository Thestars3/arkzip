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

#ifndef UFP_HPP
#define UFP_HPP

#include <QString>
#include <QFileInfo>

/*사용자 함수 묶음.\n
  Qt 4.8.0에 기반한 함수들로 재작성됨.
  */
namespace ufp {

QString makeUniqueDir(const QFileInfo &dir);
QString extractName(QString fileName);
QString extractExtension(const QString &fileName);
QString generateUniqueName(const QString &orignalName, const QString &path, bool spliteExt = true);

enum ReplaceSystemCharOption {
	RSC_ALL,      ///< 경로 구분자를 포함하여 치환합니다.
	RSC_SAVE_PATH ///< 경로 구분자 '/'를 제외하고 치환합니다.
};
QString replaceSystemChar(QString string, ReplaceSystemCharOption option = RSC_ALL);
	
};

#endif // UFP_HPP
