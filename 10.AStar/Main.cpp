#include "A.h"
#include "Node.h"


int main() 
{
    // 그리드 생성.
    // 0: 이동 가능.
    // 1: 이동 불가(장애물).
    // 2: 시작 위치.
    // 3: 목표 위치.
    vector<vector<int>> grid =
    {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 1 },
        { 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    };

    // 맵에서 시작 위치 목표 위치 검색.
    Node* startNode = nullptr;
    Node* targetNode = nullptr;

    bool initialized = false;

    for (int y = 0; y < (int)grid.size(); y++)
    {
        if (startNode && targetNode)
        {
            initialized = true;
            break;
        }
        for (int x = 0; x < (int)grid[0].size(); x++)
        {
            if (grid[y][x] == 2)
            {
                startNode = new Node(x, y);
                grid[y][x] = 0;
                continue;
            }
            else if (grid[y][x] == 3)
            {
                targetNode = new Node(x, y);
                grid[y][x] = 0;
                continue;
            }
        }
    }

    AStar aStar;

    // 경로 탐색
    vector<Node*> path = aStar.FindPath(startNode, targetNode, grid);

    if (!path.empty())
    {
        cout << "경로를 찾았습니다. 탐색 경로 : \n";
        for (Node* node : path)
        {
            cout << "(" << node->GetPosition().x << ", " << node->GetPosition().y << ") -> ";
        }
        cout << "도착. \n";

        //print map
        cout << "경로를 맵에 표시한 결과 : \n";
        aStar.DisplayGridWithPath(grid, path);
    }
    else 
    {
        cout << "경로를 찾지 못했습니다.\n";
    }


    // targetNode는 AStar객체 내부에서 메모리 해제를 하지 않고 있으므로 메모리 해제를 해줘야 한다.
    SafeDelete(targetNode);
}