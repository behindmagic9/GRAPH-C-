#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>
#include <stack>
#include <set>
#include <algorithm>
#include <climits>

class Edge
{
    int E_id{};
    int Distance{};

public:
    Edge() = default;
    Edge(int id, int distance) : E_id{id}, Distance{distance} {}

    const int get_id() const
    {
        return E_id;
    }

    const int &get_distance() const
    {
        return Distance;
    }
    const void set_distance(int distance)
    {
        Distance = distance;
    }
    bool operator==(const int &value) const
    {
        return E_id == value;
    }
};

class Vertex
{
    int V_id{};
    std::string Name{};
    int distance{};
    int predecessor{};

public:
    Vertex() = default;
    std::list<Edge> edges;
    Vertex(int id, std::string name) : V_id{id}, Name{name} {}

    const int &get_predecessor() const
    {
        return predecessor;
    }

    const void set_predecessor(const int &path)
    {
        predecessor = path;
    }

    const int &get_distance() const
    {
        return distance;
    }
    const void set_distance(const int &num)
    {
        distance = num;
    }

    const int &get_id() const
    {
        return V_id;
    }
    const void set_name(const std::string &name)
    {
        Name = name;
    }

    const std::string &get_name() const
    {
        return Name;
    }

    void printEdgeList()
    {
        std::cout << " [ ";
        for (const auto n : edges)
        {
            std::cout << std::setw(6) << n.get_id() << std::setw(6) << n.get_distance() << std::setw(6) << " --> ";
        }
        std::cout << " ] \n"
                  << std::endl;
    }

    bool checkIfEdgeexist(const int &id)
    {
        for (auto &ed : edges)
        {
            if (ed.get_id() == id)
            {
                return true;
            }
        }
        return false;
    }
    bool operator==(const int &value) const
    {
        return V_id == value;
    }
    bool operator>(const Vertex &rhs) const
    {
        return get_distance() > rhs.get_distance();
    }
    bool operator<(const Vertex &other) const
    {
        return get_distance() < other.get_distance();
    }
};

class Graph
{
public:
    Graph() = default;
    std::vector<Vertex> vertices;

    void insert(const Vertex &newvertex)
    {
        if (!checkIfvertexExist(newvertex.get_id()))
        {
            vertices.push_back(newvertex);
            std::cout << "Added succesfully" << std::endl;
        }
        else
        {
            std::cout << "Already exist in the graph " << std::endl;
        }
    }

    void addEdge(const int &source, const int &destination, const int &distance)
    {
        if (checkIfvertexExist(source) && checkIfvertexExist(destination))
        {
            for (auto &n : vertices)
            {
                if (n.get_id() == source)
                {
                    if (checkIfEdgeExist(source, destination))
                    {
                        std::cout << "Already exist edge" << std::endl;
                    }
                    else
                    {
                        Edge e(destination, distance);
                        n.edges.push_back(e);
                        std::cout << "Added succesfully" << std::endl;
                    }
                    break;
                }
            }
        }
        else
        {
            std::cout << "Either of Vertex not exist  " << std::endl;
        }
    }

    void UpdateEdge(const int &source, const int &destination, const int &distance)
    {
        if (checkIfvertexExist(source) && checkIfvertexExist(destination))
        {
            for (auto &n : vertices)
            {
                if (n.get_id() == source)
                {
                    if (checkIfEdgeExist(source, destination))
                    {
                        // update
                        auto it = std::find(n.edges.begin(), n.edges.end(), destination);
                        it->set_distance(distance);
                        std::cout << "\nUpdated successfully\n"
                                  << std::endl;
                    }
                    else
                    {
                        std::cout << "\nEdge does not exist between the source and destination\n"
                                  << std::endl;
                    }
                    break;
                }
            }
        }
        else
        {
            std::cout << "Either of vertex not exist  " << std::endl;
        }
    }

    void UpdateVertex(const int &id, const std::string &name)
    {
        auto it = std::find_if(vertices.begin(), vertices.end(), [id](const Vertex &vec)
                               { return vec.get_id() == id; });
        if (it != vertices.end())
        {
            it->set_name(name);
        }
    }

    void DeleteEdge(const int &source, const int &destination)
    {
        if (checkIfvertexExist(source) && checkIfvertexExist(destination))
        {
            for (auto &n : vertices)
            {
                if (n.get_id() == source)
                {
                    if (checkIfEdgeExist(source, destination))
                    {
                        // update
                        auto it = std::find(n.edges.begin(), n.edges.end(), destination);
                        if (it != n.edges.end())
                        {
                            n.edges.erase(it);
                            std::cout << "\nDeleted successfully\n"
                                      << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "\nEdge does not exist between the source and destination\n"
                                  << std::endl;
                    }
                    break;
                }
            }
        }
        else
        {
            std::cout << "Either of vertex not exist  " << std::endl;
        }
    }
    void DeleteVector(const int &id)
    {
        if (checkIfvertexExist(id))
        {
            for (const auto vert : vertices)
            {

                auto it = std::find(vertices.begin(), vertices.end(), id);
                if (it != vertices.end())
                {
                    vertices.erase(it);
                    for (auto &n : vertices)
                    {
                        n.edges.remove_if([id](const Edge &e)
                                          { return e.get_id() == id; });
                    }
                    std::cout << "\nDeleted Vertex successfully\n"
                              << std::endl;
                }
            }
        }
    }

    void print()
    {
        std::cout << std::left << std::setw(6) << " ID " << std::setw(6) << " City_Name " << std::setw(6) << " Edge_List " << std::endl;
        for (auto &n : vertices)
        {
            std::cout << "----------------------------------------------------------------------" << std::endl;
            std::cout << std::left << std::setw(6) << n.get_id() << std::setw(6) << n.get_name() << std::setw(6) << " ---> ";
            n.printEdgeList();
        }
    }
    bool checkIfvertexExist(const int &id)
    {
        for (const auto &vec : vertices)
        {
            if (vec.get_id() == id)
                return true;
        }
        return false;
    }
    bool checkIfEdgeExist(const int &source, const int &destination)
    {

        for (const auto &vert : vertices)
        {
            if (vert.get_id() == source)
            {
                auto it = std::find(vert.edges.begin(), vert.edges.end(), destination);
                if (it != vert.edges.end())
                {
                    return true;
                }
            }
        }
        return false;
    }

    void bfs()
    {
        std::queue<int> q;
        int startindex = vertices.front().get_id();
        q.push(startindex);
        std::unordered_set<int> visited;
        visited.insert(startindex);
        while (!q.empty())
        {
            int current = q.front();
            q.pop();
            std::cout << "Visited Vertex are  " << current << std::endl;
            for (const auto &vertex : vertices)
            {
                if (vertex.get_id() == current)
                {
                    for (auto &ed : vertex.edges)
                    {
                        int id = ed.get_id();
                        if (visited.find(id) == visited.end())
                        {
                            q.push(id);
                            visited.insert(id);
                        }
                    }
                    break;
                }
            }
        }
    }
    void dfs(){
        int startindex  = vertices.front().get_id();
        std::stack<int> s;
        std::unordered_set<int> visited;
        // bool visited;
        s.push(startindex);
        visited.insert(startindex);
        while(!s.empty()){
            int current  = s.top();
            s.pop();
            std::cout << "Visted vertex are " << current << std::endl;
            for(const auto&vert : vertices){
                if(vert.get_id() == current){
                    for(const auto &ed : vert.edges){
                        int id = ed.get_id();
                        if(visited.find(id) == visited.end()){
                            s.push(id);
                            visited.insert(id);
                        }
                    }break;
                }
            }
        }
    }
    void dijkstrabellman(const int &startVertex, const int &destination)
    {
        // dijksta's implementation
        std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> pq;
        std::unordered_set<int> visited;

        // INTIALIZE SINGLE SOURCE
        for (auto &v : vertices)
        {
            if (v.get_id() == startVertex)
                v.set_distance(0);
            else
                v.set_distance(INT_MAX);
            v.set_predecessor(-1);
        }

        pq.push(vertices.at(startVertex - 1));

        while (!pq.empty())
        {
            Vertex current = pq.top();
            pq.pop();

            int u = current.get_id();

            if (visited.find(u) != visited.end())
                continue;

            visited.insert(u);

            for (const auto &edge : current.edges)
            {
                int v = edge.get_id();
                int weight = edge.get_distance();
                int newDistance = current.get_distance() + weight;

                // RELAXING
                if (newDistance < vertices.at(v - 1).get_distance())
                {
                    vertices.at(v - 1).set_distance(newDistance);
                    vertices.at(v - 1).set_predecessor(u);
                    pq.push(vertices.at(v - 1));
                }
            }
        }

        // bellman implementation here , finding the negative cycles in the graph , detecting if still distances are changing if changes , then there is negative cycle
        for (const auto &current : vertices)
        {
            for (auto &edge : current.edges)
            {
                int v = edge.get_id();
                int w = edge.get_distance();

                if (current.get_distance() != INT_MAX && current.get_distance() + w < (vertices.at(v - 1).get_distance()))
                {
                    std::cout << "The graph contains the negative cycles " << std::endl;
                    return;
                }
            }
        }

        // printing the results if not contain negayive cycles.
        std::cout << "\n\nShortest path from vertex " << startVertex << " to vertex " << destination ;

        if (destination < 1 || destination > vertices.size())
        {
            std::cout << " Invalid destination vertex.\n";
            return;
        }

        std::vector<int> path;
        int currentVertex = destination;
        int distance = vertices.at(destination - 1).get_distance();

        while (currentVertex != startVertex)
        {
            path.push_back(currentVertex);
            currentVertex = vertices.at(currentVertex - 1).get_predecessor();

            if (currentVertex == -1)
            {
                std::cout << "No path exists from vertex " << startVertex << " to vertex " << destination << ".\n";
                return;
            }
        }

        std::cout << " || Distance : " << distance << " || Path: " << startVertex;
        for (auto it = path.rbegin(); it != path.rend(); ++it)
        {
            std::cout << " -> " << *it;
        }
        std::cout << '\n' << std::endl;
    }

    int findVertexIndex(const int &id) const
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices[i] == id)
            {
                return i;
            }
        }
        return -1;
    }
    void floydWarshall(const int &start, const int &destination)
    {
        std::vector<std::vector<int>> dist(vertices.size(), std::vector<int>(vertices.size(), INT_MAX));
        std::vector<std::vector<int>> next(vertices.size(), std::vector<int>(vertices.size(), -1));

        // Initialize distance matrix and next matrix
        for (int i = 0; i < vertices.size(); i++)
        {
            dist[i][i] = 0; // diagonla elemtn to 0
            next[i][i] = i; // noting the next element

            for (const auto &edge : vertices[i].edges)
            {
                int j = findVertexIndex(edge.get_id());
                dist[i][j] = edge.get_distance();
                next[i][j] = j;
            }
        }

        // Perform Floyd-Warshall algorithm
        for (int k = 0; k < vertices.size(); k++)
        {
            for (int i = 0; i < vertices.size(); i++)
            {
                for (int j = 0; j < vertices.size(); j++)
                {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }

        // Print shortest paths using the next matrix
        // for (int i = 0; i < vertices.size(); i++)
        // {
        std::cout << "\n\nShortest paths from vertex " << vertices[start].get_id() << " (Name: " << vertices[start].get_name() << ") " ;

        // for (int j = 0; j < vertices.size(); j++)
        // {
        std::cout << "To vertex " << vertices[destination].get_id() << " (Name: " << vertices[destination].get_name() << ") || ";
        if (dist[start][destination] == INT_MAX)
        {
            std::cout << "No path" << std::endl;
        }
        else
        {
            std::cout << " Distance: " << dist[start][destination] << " ||  Path: ";
            int nextVertex = next[start][destination];

            std::cout << vertices[start].get_id();
            while (nextVertex != destination)
            {
                std::cout << " -> " << vertices[nextVertex].get_id();
                nextVertex = next[nextVertex][destination];
            }
            std::cout << " -> " << vertices[destination].get_id() << std::endl;
        }
        // }
        std::cout << '\n'<< std::endl;
        // }
    }
};

int main()
{
    Graph g;
    
    // // Add vertices and edges to the graph
    Vertex vertex1(1, "a");
    g.insert(vertex1);

    Vertex vertex2(2, "b");
    g.insert(vertex2);

    Vertex vertex3(3, "c");
    g.insert(vertex3);

    Vertex vertex4(4, "d");
    g.insert(vertex4);

    Vertex vertex5(5, "E");
    g.insert(vertex5);

    Vertex vertex6(6, "F");
    g.insert(vertex6);


    Vertex vertex7(7, "g");
    g.insert(vertex7);

    Vertex vertex8(8, "h");
    g.insert(vertex8);

    Vertex vertex9(9, "i");
    g.insert(vertex9);

    Vertex vertex10(10, "j");
    g.insert(vertex10);

    g.addEdge(1, 4, 14);
    g.addEdge(1, 2, 12);

    g.addEdge(2, 1, 21);
    g.addEdge(2, 3, 23);
    g.addEdge(2, 5, 25);
    g.addEdge(2, 8, 28);
    g.addEdge(2, 7, 27);

    g.addEdge(3, 10, 310);
    g.addEdge(3, 9, 39);
    g.addEdge(3, 4, 34);
    g.addEdge(3, 2, 32);

    g.addEdge(4, 3, 43);
    g.addEdge(4, 1, 41);

    g.addEdge(5, 6, 56);
    g.addEdge(5, 2, 52);
    g.addEdge(5, 8, 58);
    g.addEdge(5, 7, 57);

    g.addEdge(6, 5, 65);

    g.addEdge(7, 5, 75);
    g.addEdge(7, 2, 72);
    g.addEdge(7, 8, 78);

    g.addEdge(8, 2, 82);
    g.addEdge(8, 5, 85);
    g.addEdge(8, 7, 87);

    g.addEdge(9, 3, 93);

    g.addEdge(10, 3, 103);

    std::string s;
    char choice;

    while (choice != 'Q' || choice != 'q')
    {
        std::cout << "Enter B to get a BFS traversal " << std::endl;
        std::cout << "Enter Z to get a DFS traversal " << std::endl;
        std::cout << "Enter A to add  vertex: " << std::endl;
        std::cout << "Enter E for adding edge " << std::endl;
        std::cout << "Enter U for Updating distance in edge " << std::endl;
        std::cout << "Enter F for foyd-Warshell Algorithm compile " << std::endl;
        std::cout << "Enter V for Updating Vertex " << std::endl;
        std::cout << "Enter D for deleting the edge " << std::endl;
        std::cout << "Enter X for deleting the Vertex " << std::endl;
        std::cout << "Enter P for printing " << std::endl;
        std::cout << "Enter Q to quit : " << std::endl;
        std::cin >> choice;
        switch (::toupper(choice))
        {
        case 'B':
        {
            g.bfs();
            break;
        }
        case 'Z' :
        {
            g.dfs();
            break;
        }
        case 'A':
        {
            int id;
            std::string name;
            std::cout << "ENter the id : ";
            std::cin >> id;
            std::cout << "\n Wnter the name od the vertex : ";
            std::cin >> name;
            Vertex v(id, name);
            g.insert(v);
            break;
        }
        case 'F':
        {
            int start{}, destination{};
            std::cout << "Please enter the source : ";
            std::cin >> start;
            std::cout << "PLease enter the destination : ";
            std::cin >> destination;
            g.floydWarshall(start - 1, destination - 1);
            break;
        }
        case 'E':
        {
            int source, destination, distance;
            std::cout << "Enter the source id : ";
            std::cin >> source;
            std::cout << "\nEnter the destination id :";
            std::cin >> destination;
            std::cout << "\nEnter the weight of edge : ";
            std::cin >> distance;
            g.addEdge(source, destination, distance);
            break;
        }
        case 'U':
        {
            int source, destination, distance;
            std::cout << "Enter the source id : ";
            std::cin >> source;
            std::cout << "\nEnter the destination id :";
            std::cin >> destination;
            std::cout << "\nEnter the Updated weight of edge : ";
            std::cin >> distance;
            g.UpdateEdge(source, destination, distance);
            break;
        }
        case 'V':
        {
            int Vector_id;
            std::string name;
            std::cout << "Enter the source id : ";
            std::cin >> Vector_id;
            std::cout << "Enter the Updated name : ";
            std::cin >> name;
            g.UpdateVertex(Vector_id, name);
            break;
        }
        case 'D':
        {
            int source, destination, distance;
            std::cout << "Enter the source id : ";
            std::cin >> source;
            std::cout << "\nEnter the destination id :";
            std::cin >> destination;
            g.DeleteEdge(source, destination);
            break;
        }
        case 'X':
        {
            int Vector_id;
            std::cout << "Enter the source id : ";
            std::cin >> Vector_id;
            g.DeleteVector(Vector_id);
            break;
        }
        case 'P':
        {
            std::cout << "Printing : ... \n"
                      << std::endl;
            g.print();
            break;
        }
        default:
        {
            std::cout << "\nrenter the value\n"
                      << std::endl;
            break;
        }
        case 'Q':
        {
            std::cout << "\nThanks for using !! Exiting\n";
            break;
        }
        }
    }

    return 0;
}
