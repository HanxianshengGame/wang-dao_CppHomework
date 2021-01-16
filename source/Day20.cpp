// Authors: Handling
// Created by 15870 on 2020/10/14.
// This is recure

#include <bits/stdc++.h>
using namespace std;

namespace recure {
// 思路：bfs + 优先队列 （优化搜索频度，低频度的放低）

vector<pair<int,int>> dir{{-1, 0},
						  {1,0},
						  {0, -1},
						  {0,1}};
struct Point {
  int x;
  int y;
  int step;
  bool operator<(const Point &rhs) {
    return step < rhs.step;
  }
};


int BreadthSearch(const vector<vector<char>> &matrixs) {
  Point start_point;
  memset(&start_point, 0, sizeof(start_point));
  int M = matrixs.size();
  if(M == 0)
    return -1;
  int N = matrixs[0].size();

  for(int i = 0; i != M; ++i)
    for(int j = 0; j != N; ++j)
      if(matrixs[i][j] == 'a') {
        start_point.x = i;
        start_point.y = j;
        start_point.step = 0;
      }

  bool visited[M][N];
  for (int i = 0; i != M; ++i)
	for(int j = 0; j != N; ++j)
	  visited[i][j] = false;

  priority_queue<Point> que;
  Point cur, next;
  que.push(start_point);
  visited[start_point.x][start_point.y] = true;

  while(!que.empty()) {
    cur = que.top();

    que.pop();
    int x, y;

    for(int i = 0; i < 4; ++i) {
      x = cur.x + dir[i].first;
      y = cur.y + dir[i].second;
      if(x == M || x == -1 || y == N || y == -1)
		continue;
      if(matrixs[x][y] != '#' && !visited[x][y]) {
        next.x = x;
        next.y = y;
        next.step = cur.step + 1;
        if(matrixs[x][y] == 'x')
          next.step++;
        else if(matrixs[x][y] == 'r')
		  return next.step;
      }
      visited[x][y] = true;
      que.push(next);
    }

  }

}

}

