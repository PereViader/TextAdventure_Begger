
#includes <string>
#includes <vector>

using namespace std;

class PlayerAction;

class PlayerInput {

public:
	const PlayerAction GetPlayerAction() const;

private:
	const vector<string> AskForInput();
	vector<string> TokenizeString(const string&) const;
	
	string currentActionString;
}

	