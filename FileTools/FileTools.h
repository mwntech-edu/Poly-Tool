#pragma once
#include <filesystem>
#include <iostream>

namespace  POLY_TOOLS {
	namespace fs = std::filesystem;

	enum Action {
		PRINT,
		RENAME,
		MOVE,
		DELETE,
		DELETE_FOLDER,
		DELETE_FILE,
	};

	class ActionInterface {
	public:
		virtual bool FileCondition() = 0;
		virtual int FileAction(fs::path a_path) = 0;
		virtual bool FolderCondition() = 0;
		virtual int FolderAction(fs::path a_path) = 0;
	};

	class PrintAction : public ActionInterface {
	public:
		virtual bool FileCondition() {
			return true;
		}
		virtual int FileAction(fs::path a_path) {
			//std::cout << a_path << std::endl;
			return 0;
		}
		virtual bool FolderCondition() {
			return true;
		}
		virtual int FolderAction(fs::path a_path) {
			std::cout << "[" << a_path << "] "; // << std::endl; // [] 안에 출력
			return 1;
		}
	};

	class Traverse {
	private:
		Action _mode = Action::PRINT;
		fs::path _startPath;
		ActionInterface* _actionPtr;
		// Path 구조
			// cur : c:\a\b\c\d
			// src : c:\a\b\c\d\e
			// common : c:\a\b
			// des dir : \bak
			// src local : \c ~c\d\e
			//        cur - common
			// des : c:\a\b\bak\c\d\e
			//        common + des dir + src local

	public:
		Traverse(Action a_mode, fs::path a_startPath = "./") : _mode(a_mode), _startPath(a_startPath) {

			switch (a_mode)	
			{
			case POLY_TOOLS::PRINT:
				_actionPtr = new PrintAction;
				break;
			case POLY_TOOLS::RENAME:
				break;
			case POLY_TOOLS::MOVE:
				break;
			case POLY_TOOLS::DELETE:
				break;
			case POLY_TOOLS::DELETE_FOLDER:
				break;
			case POLY_TOOLS::DELETE_FILE:
				break;
			default:
				break;
			}
		}

		~Traverse() {
			delete _actionPtr;
		}

		void DepthFirstRecursive(fs::path a_path) {
			fs::directory_iterator itr(a_path);
			bool goInto = false;

			while (itr != fs::end(itr)) { // 디렉토리 안의 모든 항목에 대해 처리
				const fs::directory_entry& entry = *itr;
				fs::path funPath = entry.path();

				if (fs::is_regular_file(funPath)) {	// 파일이면
					if (_actionPtr->FileCondition()) // file condition.
						_actionPtr->FileAction(funPath); // file action
				}
				else if (fs::is_directory(funPath)) { // 디렉토리이면
					if (_actionPtr->FolderCondition()) // dir condition
						goInto = _actionPtr->FolderAction(funPath); // dir action
					if(goInto)
						DepthFirstRecursive(funPath);
				}
				else {
					std::cout << "Error!!!!" << std::endl;
				}
				itr++;
			}
			std::cout << "^ ";
			return;
		}
	};
}