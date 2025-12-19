#include <bits/stdc++.h>

using namespace std;

struct vec2 {
	size_t x, y;

	bool	operator==(const vec2& other) const {
		return x == other.x && y == other.y;
	}
};

bool	oppositeValid(vec2 src, vec2 dst, vector<vec2> vec) {
	if (src.x == dst.x || src.y == dst.y) {
		return true;
	}
	return false;
}

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
	size_t	max = 0;
	for (size_t i = 0; i < vec.size(); i ++) {
		for (size_t j = 0; j < vec.size(); j ++) {
			size_t tmp = (fabs(vec[i].x - vec[j].x) + 1) * (fabs(vec[i].y - vec[j].y) + 1);
			if (oppositeValid(vec[i], vec[j], vec) && tmp > max) {
				max = tmp;
			}
		}
	}
	cout << max << endl;
}
