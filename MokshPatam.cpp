#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef  long int li;
typedef  long long int lli;
typedef unsigned long long int ulli;
#define all(x) x.begin(),x.end()
#define pii pair<int,int>

// Problem solving Snake Ladder: on Graph:
int find_nearest_ladder(vi &Ladder_positions, int current_pos)
{
   // finds distance of start of ladder from given point.
   auto it = lower_bound(all(Ladder_positions), current_pos);
   if (it == Ladder_positions.end())
      return -1; // menans no ladder ahead.
   return *it - current_pos;
}
void valid_partition(vi &snake_pos, int distance, int curr_pos)
{
   // this functions does partition such that no snake bite comes and min throw of dices required
   //  to travel distance.
   vi out;
   int min_throw = ceil((float)distance / 6.0);

   for (int i = 0; i < min_throw; i++)
   {
      if (distance <= 6)
      {
         out.push_back(distance);
         break;
      }
      else
      {
         for (int j = 6; j > 0; j--)
         {
            if (!binary_search(all(snake_pos), curr_pos + j))
            {
               out.push_back(j);
               curr_pos += j;
               distance -= j;
               break;
            }
         }
      }
   }

   for (const auto &x : out)
   {
      printf("%d ", x);
   }
}
int climb(vector<pii> &LE, int start)
{
   // find start as point where start to climb and returns end of ladder.
   // start must be the starting point of one of the ladder
   for (const auto &x : LE)
   {
      if (start == x.first)
         return x.second;
      // printf("%d  \n",x s3);
   }
   return start;
}
void Snake_ladder(vi &Ladder_positions, vi &snake_pos, vector<pii> &LE, int start)
{

   // if we reached at end.
   if (start >= 36)
   {
      return;
   }

   // finding and climbing to next.
   int distance = find_nearest_ladder(Ladder_positions, start);

   if (distance != -1)
   {
      valid_partition(snake_pos, distance, start);
      start += distance; // going to ladder

      start = climb(LE, start); // climbing.
      Snake_ladder(Ladder_positions, snake_pos, LE, start);
   }
   else
   {
      valid_partition(snake_pos, 36 - start, start); // no ladder left only valid partition alwwed
      return;
   } // recursive call for next walking.
}
// Graphical approach:
int jump_ar[6][6]; // initially filed with 0 jump for all positions.
class Board
{
   int V;

   list<int> *l; // list for storing vertex number and snake jump.

public:
   Board(int N_squqre)
   {
      V = N_squqre + 1; // from 1 to 36 as index;
      l = new list<int>[V];
   }

   void make_edge(int u, int v, int jump = 0)
   {
      l[u].push_back(v);
      int i = (u - 1) / 6;
      int j = (u - 1) % 6;
      jump_ar[i][j] = jump;
   }

   void make_board(unordered_map<int, int> Ladder_positions, unordered_map<int, int> snake_pos)
   {

      for (int i = 1; i <= 36; i++)
      {

         if (Ladder_positions[i])
         {
            make_edge(i, Ladder_positions[i]);
            continue;
         }
         else if (snake_pos[i])
         {
            make_edge(i, snake_pos[i], snake_pos[i] - i); // negative
            continue;
         }

         for (int j = 1; j <= 6; j++) // tossing dice.
         {
            if (Ladder_positions[i + j])
            {
               make_edge(i, Ladder_positions[i + j]);
               continue;
            }
            else if (snake_pos[i + j])
            {
               make_edge(i, snake_pos[i + j]); // negative
               continue;
            }
            else if (i + j <= 36)
               make_edge(i, i + j); // noraml move.
         }
      }
      make_edge(36, 36);
   }

   void show_brd()
   {
      for (int i = 1; i <= 36; i++)
      {
         cout << i << " ->: ";
         for (const auto &x : l[i])
         {
            cout << x << " ";
         }
         cout << '\n';
      }
   }

   void distances(int start)
   {
      vi dist(37, INT_MAX);
      dist[start] = 0; // curently at start;

      vi path(37, start);
      //   path[start] = start;

      queue<int> to_explore;
      to_explore.push(start);
      int parent;
      while (!to_explore.empty())
      {
         parent = to_explore.front();

         for (const auto &x : l[parent])
         {
            if (dist[x] == INT_MAX)
            {
               dist[x] = dist[parent] + 1; // visited to this node and distance of this node from start.
               to_explore.push(x);         // add this for exploration list;

               path[x] = parent; // adding path : start to child .
               // path[x].push_back(x);
            }
         }
         to_explore.pop();
      }

      for (int i = 1; i <= 36; i++)
      {
         cout << start << " to " << i << " -: " << dist[i] << " path ||: ";
         int lmrk = i;
         while (lmrk != start)
         {
            cout << lmrk << " ";
            lmrk = path[lmrk];
         }
         cout << start << '\n';
         //   cout<<'\n';
      }
   }
};
// main for snake ladder problem.
void main_board()
{
   unordered_map<int, int> Ladder_positions({{2, 15}, {5, 7}, {9, 27}, {18, 29}, {25, 35}});
   unordered_map<int, int> snake_pos({{17, 4}, {20, 6}, {24, 16}, {32, 30}, {34, 12}});

   // cout<<Ladder_positions[92384]<<snake_pos[98237];
   //   Snake_ladder(Ladder_positions,snake_pos,LE,1);

   Board game(36);
   game.make_board(Ladder_positions, snake_pos);
    game.show_brd();
   // game.distances(1);
}



int main()
{
  
  main_board();

}