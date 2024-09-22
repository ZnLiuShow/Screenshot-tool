#include "pch.h"
#include "W_Screenshot.h"
#include "ScreenShotDlg.h"

namespace fs = std::filesystem;
Screenshot pre_mss;
extern 	CScreenShotDlg dlg;
void resizecutmat(cv::Mat& originalImage, cv::Mat& resizedImage, int width, int hight);

void process_screen() {	
	int width = dlg.TarWinRect.right - dlg.TarWinRect.left;
	int hight = dlg.TarWinRect.bottom - dlg.TarWinRect.top;
	cv::Mat cutsc = pre_mss.getScreenshot(dlg.TarWinRect.left, dlg.TarWinRect.top, width, hight);
	CString outdir;
	dlg.SCEDITOUTDIR.GetWindowTextW(outdir);
	CString num;
	num.Format(L"%d", dlg.cutsc_count);
	outdir += L"\\" + num + L".jpg";
	//AfxMessageBox(outdir);
	CStringA outdira(outdir.GetString());
	if (width == dlg.outimg_width && hight == dlg.outimg_hight)	{
		cv::imwrite(outdira.GetString(), cutsc);
	}
	else {
		cv::Mat recutsc;
		resizecutmat(cutsc, recutsc, dlg.outimg_width, dlg.outimg_hight);
		cv::imwrite(outdira.GetString(), recutsc);
	}
	dlg.cutsc_count++;
}

void resizecutmat(cv::Mat& originalImage, cv::Mat& resizedImage, int width,int hight) {
	cv::Size newSize(width,hight);
	cv::resize(originalImage, resizedImage, newSize, 0, 0, cv::INTER_LINEAR);
}

bool directory_exists(const fs::path& dir_path) {
	return fs::exists(dir_path) && fs::is_directory(dir_path);
}

char myoutdir[MAX_PATH];

void autowokedir() {
	if (!directory_exists(myoutdir))
	{
		fs::create_directories(myoutdir);
	}
}