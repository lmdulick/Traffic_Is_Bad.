#include "AdjList.h"

AdjList::AdjList() {
	//create empty map
	state_to_county = map<string, vector<County>>();
}

AdjList::~AdjList() {
	//empty map 
	state_to_county.clear();
}

//return county object of specified county 
County AdjList::GetCountyObj(string state, string county) {
	auto itr = state_to_county.find(state);
	for (int i = 0; i < itr->second.size(); i++) {  
		if (itr->second[i].GetCounty() == county) { 
			return itr->second[i];  
		}
	}
	County obj; 
	return obj; 
}

//return true if key not found in map 
bool AdjList::CheckState(string state) {
	if (state_to_county.find(state) == state_to_county.end()) {
		return true;
	}

	return false;

}

//return true if not found in map already
bool AdjList::CheckCounty(string state, string county) {
	if (!CheckState(state)) {   
		auto it = state_to_county.find(state);
		for (int i = 0; i < it->second.size(); i++) {
			if (it->second[i].GetCounty() == county) {
				return false;
			}
		}
	}
	return true;
}

//adds/edits specified county and state 
void AdjList::AddCounty(string state, string county_, string severity, string visibility, string w_con, string crossing, string junction, string stop, string signal, string time) { 
	County county;
	//if county isn't in the specific state 
	if (CheckCounty(state, county_)) {
		//must create county object then edit it
		county.AddCountyAndState(county_, state);  
		county.AddToTotalCrashes();
		county.AddSeverity(severity);
		county.AddVisibility(visibility);
		county.ChangeWeather(w_con);
		county.AddCrossing(crossing);
		county.AddJunction(junction);
		county.AddStop(stop);
		county.AddSignal(signal);
		county.AddDayOrNight(time);
		state_to_county[state].push_back(county);
	}
	else {
		//edits existing county data (add 1 more accident)
		auto itr = state_to_county.find(state);
		for (int i = 0; i < itr->second.size(); i++) {
			if (itr->second[i].GetCounty() == county_) {
				itr->second[i].AddToTotalCrashes();
				itr->second[i].AddSeverity(severity); 
				itr->second[i].AddVisibility(visibility); 
				itr->second[i].ChangeWeather(w_con); 
				itr->second[i].AddCrossing(crossing); 
				itr->second[i].AddJunction(junction);
				itr->second[i].AddStop(stop); 
				itr->second[i].AddSignal(signal);
				itr->second[i].AddDayOrNight(time);  
			}
		}
	}
}

//prints states and coutnies data 
void AdjList::PrintTesting() {
	for (auto i = state_to_county.begin(); i != state_to_county.end(); i++) {
		cout << i->first << ": " << endl;
		for (int j = 0; j < i->second.size(); j++) {
			cout << i->second[j].GetCounty() << ": " << endl;
			cout << i->second[j].GetAvgSeverity() << ", " << i->second[j].GetAvgVisibility() << ", " << i->second[j].GetWeather("Fair") << ", " << i->second[j].GetWeather("Cloudy") << ", " << i->second[j].GetWeather("Rain") << ", ";
			cout << i->second[j].GetWeather("Fog") << ", " << i->second[j].GetWeather("Snow") << ", " << i->second[j].GetCrossing() << ", " << i->second[j].GetJunction() << ", " << i->second[j].GetStop() << ", ";
			cout << i->second[j].GetSignal() << ", " << i->second[j].GetDay() << ", " << i->second[j].GetNight() << ", " << i->second[j].GetTotalCrashes() << endl;
		}
		cout << endl;
	}
}

//prints the total crashes of the whole map (every county in every state)
void AdjList::PrintTotalCrashes() {
	int sum = 0;
	for (auto it = state_to_county.begin(); it != state_to_county.end(); it++) {
		for (int i = 0; i < it->second.size(); i++) {
			sum += it->second[i].GetTotalCrashes();
		}
	}
	cout << "total crashes: " << sum << endl;
}
 