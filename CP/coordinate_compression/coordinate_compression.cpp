#include "coordinate_compression.h"
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// COORDINATE COMPRESSION — Demo (class → coordinate_compression.h)
// ════════════════════════════════════════════════════════════════════════════

int main()
{
    vector<int> arr = {1000, 50, 1000, 200, 50, 1};

    cout << "Original Array: ";
    for (int x : arr)
        cout << x << " ";
    cout << "\n\n";

    Coordinate_Compression cc(arr);

    cout << "Compression Mapping (original -> compressed):\n";
    for (auto [val, id] : cc.compress)
        cout << "   " << val << " -> " << id << "\n";

    cout << "\nReverse Mapping (compressed -> original):\n";
    for (int i = 0; i < (int)cc.rev_map.size(); i++)
        cout << "   " << i << " -> " << cc.rev_map[i] << "\n";

    vector<int> compressed = cc.get_compressed(arr);

    cout << "\nCompressed Array: ";
    for (int x : compressed)
        cout << x << " ";
    cout << "\n";

    cout << "\nBIT size needed: " << cc.rev_map.size() << " (instead of 1001!)\n";

    return 0;
}
