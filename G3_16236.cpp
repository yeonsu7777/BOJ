#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

const int maxN = 20;

int N;
int ocean[maxN][maxN];


struct Fish
{
	int x;
	int y;
	int dist;

	bool operator<(Fish& ref)
	{
		if (this->dist == ref.dist)
		{
			if (this->x == ref.x)
				return (this->y < ref.y);
			return (this->x < ref.x);
		}
		return (this->dist < ref.dist);
	}
};

int result = 0;
Fish babyShark;
int sharkSize = 2;
int eaten = 0;
std::vector<Fish> fishes;

void getInput()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &ocean[i][j]);
			if (ocean[i][j] == 9)
			{
				babyShark.x = i;
				babyShark.y = j;
				babyShark.dist = 0;
				ocean[i][j] = 0;
			}
		}
	}
}

bool avail(int x, int y)
{
	if (x < 0 || x >= N || y < 0 || y >= N)
		return false;
	if (sharkSize < ocean[x][y])
		return false;
	return true;
}

void BFS()
{
	std::queue<Fish> Q;
	Q.push({ babyShark.x, babyShark.y, 0 });
	int visit[20][20] = { 0, };
	int dx[4] = { -1, 0, 0, 1 };
	int dy[4] = { 0, -1, 1, 0 };
	visit[babyShark.x][babyShark.y] = 1;

	while (!Q.empty())
	{
		int curX = Q.front().x;
		int curY = Q.front().y;
		int curD = Q.front().dist;
		Q.pop();

		if (ocean[curX][curY] > 0 && ocean[curX][curY] < sharkSize)
		{
			Fish newFish = { curX, curY, curD };
			fishes.push_back(newFish);
		}

		for (int i = 0; i < 4; i++)
		{
			int nextX = curX + dx[i];
			int nextY = curY + dy[i];
			if (avail(nextX, nextY))
			{
				if (!visit[nextX][nextY])
				{
					Q.push({ nextX, nextY, curD + 1 });
					visit[nextX][nextY] = 1;
				}
			}
		}
	}
}

void solve()
{
	while (true)
	{
		fishes.clear();
		BFS();
		std::sort(fishes.begin(), fishes.end());
		if (fishes.size() == 0)
			break;

		babyShark.x = fishes[0].x;
		babyShark.y = fishes[0].y;
		babyShark.dist += fishes[0].dist;
		ocean[babyShark.x][babyShark.y] = 0;

		eaten++;
		if (eaten == sharkSize)
		{
			eaten = 0;
			sharkSize++;
		}
	}

	printf("%d", babyShark.dist);
}


int main()
{
	getInput();
	solve();
}