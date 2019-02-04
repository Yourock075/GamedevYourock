#include <cstdlib>
#include <iostream>

#include <SDL2/SDL_version.h>

std::ostream& operator << (std::ostream& out, const SDL_version& s)
{
    out << static_cast<int>(s.major);
    out << static_cast<int>(s.minor);
    out << static_cast<int>(s.patch);

}

int main(int /*argc*/, char* /*argv*/ [])
{
    using namespace std;

        SDL_version compiled = { 0, 0, 0 };
        SDL_version linked   = { 0, 0, 0 };

        SDL_VERSION(&compiled);
        SDL_VERSION(&linked);

        cout << "compiled: " << compiled << '\n';
        cout << "linked: " << linked << endl;

        bool is_good = cout.good();

        return is_good ? EXIT_SUCCESS : EXIT_FAILURE;
}
