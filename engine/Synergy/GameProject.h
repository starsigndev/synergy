#pragma once
#include <string>
#include <vector>
class GameProject
{
public:

	GameProject();
	void SetName(std::string name) { _Name = name; }
	std::string GetName() { return _Name; }
	void SetAuthor(std::string author) { _Author = author; }
	std::string GetAuthor() { return _Author; }
	void SetCopyright(std::string copyright) { _Copyright = copyright; }
	std::string GetCopyright() { return _Copyright; }
	void SetSplashImage(std::string path) { _SplashImagePath = path; }
	std::string GetSplashImage() { return _SplashImagePath; }
	void SetIntroMovie(std::string path) { _IntroMoviePath = path; }
	std::string GetIntroMovie() { return _IntroMoviePath; }

	void Save();
	void Load();

	static GameProject* Project;

private:

	std::string _Name = "";
	std::string _Author = "";
	std::string _Copyright = "";
	std::string _SplashImagePath = "";
	std::string _IntroMoviePath = "";

};

