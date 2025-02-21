#include "A.h"
#include "Node.h"


int main() 
{
    // �׸��� ����.
    // 0: �̵� ����.
    // 1: �̵� �Ұ�(��ֹ�).
    // 2: ���� ��ġ.
    // 3: ��ǥ ��ġ.
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

    // �ʿ��� ���� ��ġ ��ǥ ��ġ �˻�.
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

    // ��� Ž��
    vector<Node*> path = aStar.FindPath(startNode, targetNode, grid);

    if (!path.empty())
    {
        cout << "��θ� ã�ҽ��ϴ�. Ž�� ��� : \n";
        for (Node* node : path)
        {
            cout << "(" << node->GetPosition().x << ", " << node->GetPosition().y << ") -> ";
        }
        cout << "����. \n";

        //print map
        cout << "��θ� �ʿ� ǥ���� ��� : \n";
        aStar.DisplayGridWithPath(grid, path);
    }
    else 
    {
        cout << "��θ� ã�� ���߽��ϴ�.\n";
    }


    // targetNode�� AStar��ü ���ο��� �޸� ������ ���� �ʰ� �����Ƿ� �޸� ������ ����� �Ѵ�.
    SafeDelete(targetNode);
}