#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "../../Configuration/Configuration.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include <wx/thread.h>

wxDECLARE_EVENT(wxEVT_COPIERDONE, wxCommandEvent);

class ModCopier final: public wxThread
{
  public:
	explicit ModCopier(wxEvtHandler* pParent): wxThread(wxTHREAD_DETACHED), m_pParent(pParent) {}
	void loadConfiguration(const std::shared_ptr<Configuration>& theConfiguration) { configuration = theConfiguration; }

  private:
	void* Entry() override;
	void createPlayset(const std::filesystem::path& destModFolder, const std::filesystem::path& targetName, bool metadataApproach);
	[[nodiscard]] static std::filesystem::path getLastUpdatedLauncherDbPath(const std::filesystem::path& gameDocsDirectory);
	void deactivateCurrentPlayset(SQLite::Database& db);
	[[nodiscard]] static std::string addModToDb(SQLite::Database& db,
		 const std::string& modName,
		 const std::string& gameRegistryId,
		 const std::string& dirPath,
		 bool metadataApproach);
	void addModToPlayset(SQLite::Database& db, const std::string& modID, const std::string& playsetID);

	std::shared_ptr<Configuration> configuration;

  protected:
	wxEvtHandler* m_pParent;
};
