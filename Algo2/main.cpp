#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

struct job {
	int a1,a2,a3;
};

struct work {
	int end, spend;

	work(int end, int spend) {
		this->end = end;
		this->spend = spend;
	}
};

bool operator<(const work w1, const work w2)
{
	return w1.end < w2.end;
}

job* jobs;
int n, m;

bool myfunc(job j1, job j2) {
	return j1.a1 < j2.a1;
}

int analyze() {
	int ans = 0;
	int cur_time = 0;
	int last_free = -1;
	queue<job> queue;
	priority_queue<work> working;
	for (int i = 0; i < n; i++)
		queue.push(jobs[i]);
	while (!queue.empty() || !working.empty())
	{
		if (working.size() < n && !queue.empty())
		{
			job j = queue.front();
			working.push(work(last_free+1, j.a3));
			continue;
		}

		work t = working.top();
		working.pop();
		ans = max(ans, t.end + t.spend);
		last_free = t.end;
	}
	return ans;
}

int main() {
	ifstream in("input.txt");
	in >> n >> m;
	jobs = new job[n];
	for (int i = 0; i < n; i++)
		in >> jobs[i].a1 >> jobs[i].a2 >> jobs[i].a3;
	
	sort(jobs, jobs+n, myfunc);

	int res = analyze();

	return 0;
}