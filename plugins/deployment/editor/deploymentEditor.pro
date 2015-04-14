# Copyright 2007-2015 QReal Research Group
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

QREAL_XML = deploymentEditor.xml
QREAL_XML_DEPENDS =  ../../commonMetamodels/kernelMetamodel.xml ../../commonMetamodels/basicBehaviorsMetamodel.xml ../../commonMetamodels/basicActionsMetamodel.xml
QREAL_EDITOR_PATH = deployment/editor
ROOT = ../../..

include (../../editorsSdk/editorsCommon.pri)

win32 {
	win32:DESTDIR ~= s,/,\,g
	QMAKE_POST_LINK = "cmd /C "xcopy images $$DESTDIR\\images /s /e /q /y /i &&"\
			"xcopy ..\\scripts $$DESTDIR\\deployment-scripts /s /e /q /y /i &&""
}
else {
	QMAKE_POST_LINK = "cp -r images $$DESTDIR/; "\
					"mkdir $$DESTDIR/deployment-scripts; "\
					"cp -r ../scripts/* $$DESTDIR/deployment-scripts"
}
