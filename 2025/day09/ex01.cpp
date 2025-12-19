#include <bits/stdc++.h>

using namespace std;

struct vec2 {
	long long int x, y;
};

int	main(int ac, char **av) {
	string	s;
	fstream	fs(av[1]);
	vector<vec2>	vec;
	while(getline(fs, s)) {
		vec2	v;
		v.x = atol((s.substr(0, s.find(","))).c_str());
		v.y = atol((s.substr(s.find(",") + 1)).c_str());
		vec.push_back(v);
	}
	long long int	max = (abs(vec[0].x - vec[1].x) + 1) * (abs(vec[0].y - vec[1].y) + 1);
	for (size_t i = 0; i < vec.size(); i ++) {
		for (size_t j = 0; j < vec.size(); j ++) {
			long long int tmp = (abs(vec[i].x - vec[j].x) + 1) * (abs(vec[i].y - vec[j].y) + 1);
			if (tmp > max) {
				max = tmp;
			}
		}
	}
	cout << max << endl;
}
