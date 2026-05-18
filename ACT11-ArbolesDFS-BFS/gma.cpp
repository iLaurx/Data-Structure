#include <iostream>
#include <vector>
#include <queue>

class GrafoMA
{
    private:
    std::vector< std::vector<int> > G;
    int N;
    bool dirigido;
    bool ponderado;
    
    // Función auxiliar recursiva para DFS
    bool _dfs_recursivo(int current, int end, std::vector<bool>& visited, std::vector<int>& path) 
    {
        visited[current] = true;
        path.push_back(current);

        // Caso Base: Si es la meta
        if (current == end) {
            return true;
        }

        // Explorar los vecinos en la matriz de adyacencia
        for (int v = 0; v < N; ++v) {
            // Si hay conexión y no ha sido visitado
            if (G[current][v] != 0 && !visited[v]) {
                if (_dfs_recursivo(v, end, visited, path)) {
                    return true;
                }
            }
        }

        // Si ningún vecino encontró camino, hacemos pop (Backtracking)
        path.pop_back();
        return false;
    }

    public:
    
    GrafoMA(int size, bool d, bool p)
    {
        N = size;
        dirigido = d;
        ponderado = p;
        
        G.resize(N, std::vector<int>(N, 0));
    }
    
    void agregar(int i, int j, int peso)
    {
        if(ponderado)
        {
            G[i][j] = peso;
            if(!dirigido)
                G[j][i] = peso;
        }
        else
        {
            G[i][j] = 1;
            if(!dirigido)
                G[j][i] = 1;
        }
    }
    
    void imprimir()
    {
        for(int i=0; i<N; ++i)
        {
            std::cout << "[";
            for(int j=0; j<N; ++j)
            {
                if(j)
                    std::cout << ",\t" << G[i][j];
                else
                    std::cout << G[i][j];
            }
            std::cout << "]\n";
        }
    }

    // Búsqueda en Anchura
    // Encuentra el camino más corto en grafos no ponderados
    std::vector<int> find_path_bfs(int start, int end) 
    {
        std::queue<std::vector<int>> queue;
        std::vector<bool> visited(N, false);

        queue.push({start});
        visited[start] = true;

        while (!queue.empty()) {
            std::vector<int> path = queue.front();
            queue.pop();
            
            int node = path.back();

            if (node == end) {
                return path;
            }

            // Exploramos los vecinos del nodo actual
            for (int v = 0; v < N; ++v) {
                if (G[node][v] != 0 && !visited[v]) {
                    visited[v] = true;
                    
                    std::vector<int> new_path = path;
                    new_path.push_back(v);
                    queue.push(new_path);
                }
            }
        }
        return {}; // Retorna un vector vacío si no hay ruta
    }

    // Búsqueda en Profundidad
    std::vector<int> find_path_dfs(int start, int end) 
    {
        std::vector<bool> visited(N, false);
        std::vector<int> path;
        
        if (_dfs_recursivo(start, end, visited, path)) {
            return path;
        }
        return {}; // Retorna un vector vacío si no hay ruta
    }
};

// Función de utilidad para imprimir el formato de los arreglos
void print_path(const std::vector<int>& path) {
    if (path.empty()) {
        std::cout << "None\n";
        return;
    }
    std::cout << "[";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i] << (i == path.size() - 1 ? "" : ", ");
    }
    std::cout << "]\n";
}

int main(void)
{
    GrafoMA gma(6, false, false);
    
    gma.agregar(0, 1, 1);
    gma.agregar(0, 2, 1);
    gma.agregar(1, 2, 1);
    gma.agregar(2, 3, 1);
    gma.agregar(2, 4, 1);
    gma.agregar(3, 5, 1);
    
    std::cout << "Matriz de Adyacencia:\n";
    gma.imprimir();
    std::cout << "----------------------------------------\n";
    
    int start = 0;
    int end = 5;

    std::cout << "--- Probando recorrido DFS ---\n";
    std::vector<int> path_dfs = gma.find_path_dfs(start, end);
    std::cout << "Camino DFS encontrado: ";
    print_path(path_dfs);

    std::cout << "----------------------------------------\n";

    std::cout << "--- Probando recorrido BFS ---\n";
    std::vector<int> path_bfs = gma.find_path_bfs(start, end);
    std::cout << "Camino BFS encontrado: ";
    print_path(path_bfs);

    return 0;
}