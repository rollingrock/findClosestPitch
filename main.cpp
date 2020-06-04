#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <math.h>



using namespace std;

struct POINT {
	float x;
	float y;
};

float dist(POINT a, POINT b) {
	return abs(sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));;
}

float stripSearch(vector<POINT> a_vec, float d) {
	float minD = d;
	sort(a_vec.begin(), a_vec.end(),
		[](const POINT& a, const POINT& b) -> bool {
		return a.y < b.y;
	}
	);

	for (auto i = a_vec.begin(); i != a_vec.end(); i++) {
		for (auto j = i + 1; (j != a_vec.end()) && (abs(j->y - i->y) < minD); j++) {
			float ret = dist(*i, *j);
			if (ret < minD)
				minD = d;
		}
	}

	return minD;
}

float closest(vector<POINT> a_vec) {
	float minD = FLT_MAX;

	if (a_vec.size() < 5) {
		for (auto i = a_vec.begin(); i != a_vec.end(); i++)
			for (auto j = i + 1; j != a_vec.end(); j++) {
				if (dist(*i, *j) < minD) {
					minD = dist(*i, *j);
				}
			}

		return minD;
	}

	int mp = a_vec.size() / 2;

	vector<POINT> lh;
	vector<POINT> rh;

	for (auto i = 0; i < mp; i++)
		lh.push_back(a_vec[i]);

	for (auto i = mp; i < a_vec.size(); i++)
		rh.push_back(a_vec[i]);

	float left = closest(lh);
	float right = closest(rh);

	minD = min(left, right);

	vector<POINT> strip;
	float midx = lh.back().x;

	for (auto i = a_vec.begin(); i != a_vec.end(); i++) {
		if (abs((i->x - midx) < minD)) {
			strip.push_back(*i);
		}
	}

	if (strip.size() != 0) {
		minD = stripSearch(strip, minD);
	}

	return minD;
}


int main() {
	vector<POINT> vP;

	fstream file;

	file.open("c:\\points.txt");

	if (file.fail()) {
		cout << "cannot open file" << endl;
		return 0;
	}

	POINT p;

	while (file >> p.x >> p.y) {
		vP.push_back(p);
	}

	sort(vP.begin(), vP.end(),
		[](const POINT& a, const POINT& b) -> bool {
			return a.x < b.x;
		}
	);


	//for (auto i = vP.begin(); i != vP.end(); ++i) {
	//	cout << i->x << " " << i->y << endl;
	//}

	float result = closest(vP);

	cout << result << endl;

	return 0;
}