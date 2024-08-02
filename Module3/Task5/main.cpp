// Найдите приближенное решение метрической неориентированной задачи коммивояжера в полном графе(на плоскости) с помощью минимального остовного дерева.
// Оцените качество приближения на случайном наборе точек, нормально распределенном на плоскости с дисперсией 1. 
// Нормально распределенный набор точек получайте с помощью преобразования Бокса - Мюллера.
// При фиксированном N, количестве вершин графа, несколько раз запустите оценку качества приближения.
// Вычислите среднее значение и среднеквадратичное отклонение качества приближения для данного N.
// Запустите данный эксперимент для всех N в некотором диапазоне, например, [2, 10].
// Автоматизируйте запуск экспериментов.
// В решении требуется разумно разделить код на файлы. Каждому классу - свой заголовочный файл и файл с реализацией.

//Вариант 2. Для построения минимального остовного дерева используйте алгоритм Прима.


#include "WeightedGraph.h"
#include "BoxMuller.h"

void Run(std::istream& input, std::ostream& output)
{
    int N = 0; // количество вершин
    int M = 0; // количество рёбер

    int v1 = 0; // первая вершина инцидентная вставляемому ребру
    int v2 = 0; // вторая вершина инцидентная вставляемому ребру
    int weight = 0; // вес ребра между вершинами v1 и v2

    int u = 0; // начальная вершина
    int w = 0; // конечная вершина

    input >> N;
    WeightedListGraph g(N);
    input >> M;
    for (int i = 0; i < M; ++i)
    {
        input >> v1 >> v2 >> weight;
        g.AddEdge(v1 - 1, v2 - 1, weight);
        g.AddEdge(v2 - 1, v1 - 1, weight);
    }
    output << g.GetMSTWeight();
}


void TestGetMSTWeight() // функция тестирования работоспособности алгоритма нахождения минимального остовного дерева
{
    {
        std::stringstream output;
        std::stringstream input;
        input << "4 4 1 2 1 2 3 2 3 4 5 4 1 4";
        Run(input, output);
        assert(output.str() == "7");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "5 10 4 3 3046 4 5 90110 5 1 57786 3 2 28280 4 3 18010 4 5 61367 4 1 18811 4 2 69898 3 5 72518 3 1 85838";
        Run(input, output);
        assert(output.str() == "107923");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "5 7 1 3 4 1 2 2 2 3 1 2 4 3 4 5 2 3 5 3 4 3 5";
        Run(input, output);
        assert(output.str() == "8");
    }

    {
        std::stringstream output;
        std::stringstream input;
        input << "5 7 1 2 10 1 4 15 2 3 12 2 5 8 3 5 10 4 5 11 1 3 6";
        Run(input, output);
        assert(output.str() == "35");
    }
}


int main()
{
    //TestGetMSTWeight(); // функция тестирования работоспособности алгоритма нахождения минимального остовного дерева

    int number_of_vertexes = 10; // максимальное количество вершин до которого алгоритм будет итерироваться (максимальное значение - 10; при большем количестве алгоритм не работает)
    int iteration_count = 20; // количество итераций для каждого количества вершин
    std::vector<std::vector<std::pair<float, float>>> matrix_of_paths(number_of_vertexes, std::vector<std::pair<float, float>>(iteration_count)); // first - приближённое вычисление, second - точное вычисление
    for (int N = 3; N < number_of_vertexes; ++N) // итерирование по количеству вершин
    {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "================= N=" << N << " =================" << std::endl;
        for (int iteration = 0; iteration < iteration_count; ++iteration) // прогон множества "экспериментов" для одного и того же количества вершин
        {
            WeightedListGraph g(N);
            std::vector< std::pair<float, float>> point_vector(N); // создание нормально распределенного набора точек с помощью преобразования Бокса - Мюллера
            for (int i = 0; i < N; ++i)
            {
                std::pair<float, float> point = GetNormalRandPoint();
                point_vector[i] = (point);
            }

            for (int i = 0; i < (N - 1); ++i) // добавление точек, полученных на предыдущем шаге, в граф с сопутствующим вычислением весов рёбер
            {
                for (int j = i + 1; j < N; ++j)
                {

                    float projection_by_x = point_vector[i].first - point_vector[j].first; // проекция по х
                    float projection_by_y = point_vector[i].second - point_vector[j].second; // проекция по y
                    float distance = sqrt((projection_by_x * projection_by_x) + (projection_by_y * projection_by_y));
                    g.AddEdge(i, j, distance);
                    g.AddEdge(j, i, distance);
                }
            }

            std::string s = "";

            for (int i = 0; i < N; ++i) // создание строки "0123456789"
            {
                s += std::to_string(i);
            }

            float min_path = SIZE_MAX; // минимальный путь

            do // перебор всех возможных комбинаций символов в строке
            {
                std::vector<int> vertex_vector(N);
                for (int i = 0; i < N; ++i) // перевод строковых данных к числовым
                {

                    int vertex = int(s[i]) - int('0');
                    vertex_vector[i] = vertex;

                }
                float path_length = 0; // длина замкнутого пути для текущей комбинации символов
                for (int i = 1; i < N; ++i) // вычисление длины замкнутого пути для текущей комбинации символов
                {
                    float weight = g.GetWeight(vertex_vector[i - 1], vertex_vector[i]);
                    path_length += weight;
                }
                path_length += g.GetWeight(vertex_vector[N - 1], vertex_vector[0]); // чтобы цикл был замкнутым, нужно соединить последнюю и начальную вершины 
                if (min_path > path_length) // если очередной вычисленный путь меньше минимальноего, то осуществляем перезапись
                {
                    min_path = path_length;
                }
            } while (std::next_permutation(s.begin(), s.end()));

            WeightedListGraph mst(N);
            mst = g.GetMST(); // получаем минимальное остовное дерево 
            std::vector<int> dfs_vertex_list = mst.DFS(); // получаем вершины минимального остовного дерева в порядке обхода в глубину
            float approximate_min_path_length = 0;
            for (int i = 1; i < N; ++i) // по упорядоченному набору вершин считаем длину замкнутого пути 
            {
                float weight = g.GetWeight(dfs_vertex_list[i - 1], dfs_vertex_list[i]);
                approximate_min_path_length += weight;
            }
            approximate_min_path_length += g.GetWeight(dfs_vertex_list[N - 1], dfs_vertex_list[0]); // чтобы цикл был замкнутым, нужно соединить последнюю и начальную вершины 


            std::cout << "N = " << N << " Iteration = " << iteration << " APPROXIMATE min_path: " << approximate_min_path_length << std::setprecision(10) << '\n';
            std::cout << "N = " << N << " Iteration = " << iteration << " ACCURATE min_path   : " << min_path << std::setprecision(10) << '\n';
            std::cout << "---------------------------------------" << std::endl;

            std::pair<float, float> pair_to_insert;
            pair_to_insert.first = approximate_min_path_length;
            pair_to_insert.second = min_path;
            matrix_of_paths[N][iteration] = pair_to_insert;
        }
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    for (int i = 3; i < number_of_vertexes; ++i) // вычисляем среднее значение отклонения
    {
        double sum_of_division_results = 0;
        for (int j = 0; j < iteration_count; ++j)
        {
            double division_result = matrix_of_paths[i][j].first / matrix_of_paths[i][j].second;
            sum_of_division_results += division_result;
        }
        double mean_value = sum_of_division_results / iteration_count;
        double difference_between_accurate_and_approximate_path_percent = (mean_value - 1) * 100;
        std::cout << "N = " << i << "; Mean Difference     = " << difference_between_accurate_and_approximate_path_percent << " %" << '\n';

        double sum = 0; // sum((xi - xm)^2)
        for (int j = 0; j < iteration_count; ++j) // вычисляем среднеквадратичное отклонение отклонения качества приближения
        {
             
            double division_result = matrix_of_paths[i][j].first / matrix_of_paths[i][j].second;
            double summand = (division_result - mean_value) * (division_result - mean_value); // каждый множитель по идее должен быть ((division_result - 1) - (mean_value - 1)), но -1 взаимоуничтожаются
            sum += summand;
        }
        double result_after_division = sum / iteration_count; // sum((xi - xm)^2) / n
        double mean_squared_error = sqrt(result_after_division);
        std::cout << "N = " << i << "; Mean Squared Error  = " << mean_squared_error * 100 << " %" << '\n';
        std::cout << "---------------------------------------" << std::endl;
    }

    return 0;
}

