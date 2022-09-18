#include "ScoreMan.hpp"

using namespace std;

void Engine::ScoreMan::SetScore(int score, string s_name) {
	ifstream reader("ranking/highscores.txt");
	Score scores[10];
	string name;
	int scoreFile;
	for (int i = 0; i < 10; ++i) {
		reader >> name >> scoreFile;
		scores[i] = Score() = { name, scoreFile };
	}

	sort(scores, scores + 10, [](Score& r1, Score r2) {return r1.score > r2.score; });
	if (scores[9].score < score) { 
		scores[9] = Score() = { s_name, score };
	}

	sort(scores, scores + 10, [](Score& r1, Score r2) {return r1.score > r2.score; });
	fstream rewrite("ranking/highscores.txt", ios::out);
	for (int i = 0; i < 10; ++i)
		rewrite << scores[i].name << '\t' << scores[i].score << '\n';
	rewrite.close();
}

string Engine::ScoreMan::GetFromFile(string filename, int separator) {
	string text, line;
	ifstream reader("ranking/"+filename);
	int p = 1;
	while (getline(reader, line)) {
		text += to_string(p) + ". \t" + line + (separator == -1 ? "\n" : "");
		p++;
	}
		
	if (separator != -1)
		for (int i = 0; i < text.size(); i += separator)
			text = text.substr(0, i) + '\n' +  text.substr(i, text.size());

	return text;
}