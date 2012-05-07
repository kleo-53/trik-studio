#include "findManager.h"

FindManager::FindManager(qrRepo::RepoControlInterface &controlApi,
						qrRepo::LogicalRepoApi &logicalApi,
						qReal::gui::MainWindowInterpretersInterface *mainWindow,
						FindReplaceDialog *findReplaceDialog,
						QObject *parent)
	: QObject(parent)
	, mControlApi(controlApi)
	, mLogicalApi(logicalApi)
	, mFindReplaceDialog(findReplaceDialog)
	, mMainWindow(mainWindow)
{
}

void FindManager::handleRefsDialog(qReal::Id const &id)
{
	mMainWindow->selectItem(id);
}

qReal::IdList FindManager::foundByMode(QString key, QString currentMode)
{
	if (currentMode == ("by name"))
		return mControlApi.findElementsByName(key);
	if (currentMode == ("by type"))
		return mLogicalApi.elementsByType(key);
	if (currentMode == ("by property"))
		return mControlApi.elementsByProperty(key);
	if (currentMode == ("by property content"))
		return mControlApi.elementsByPropertyContent(key);
}

QMap<QString, QString> FindManager::findItems(QStringList const &searchData)
{
	QMap<QString, QString> found;
	for(int i = 1; i < searchData.length(); i++) {
		qReal::IdList byMode = foundByMode(searchData.first(), searchData[i]);
		foreach (qReal::Id currentId, byMode) {
			if (found.contains(currentId.toString())) {
				found[currentId.toString()] += tr(", ") + searchData[i];
				continue;
			}
			found.insert(currentId.toString(), tr("   :: ") + searchData[i]);
		}
	}
	return found;
}

void FindManager::handleFindDialog(QStringList const &searchData)
{
	mFindReplaceDialog->initIds(findItems(searchData));
}

void FindManager::handleReplaceDialog(QStringList &searchData)
{
	if (searchData.contains("by name")) {
		qReal::IdList toRename = foundByMode(searchData.first(), "by name");
		foreach (qReal::Id currentId, toRename)
			mLogicalApi.setName(currentId, searchData[1]);
	}
	if (searchData.contains("by property content")) {
		qReal::IdList toRename = foundByMode(searchData.first(), "by property content");
		mLogicalApi.replaceProperties(toRename, searchData[0], searchData[1]);
	}
}
