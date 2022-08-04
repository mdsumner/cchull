#include "concaveman.h"
#include <cpp11.hpp>
#include <cpp11/data_frame.hpp>

using namespace cpp11;
using namespace cpp11::literals; // so we can use ""_nm syntax

[[cpp11::register]]
cpp11::data_frame cpp_concaveman(cpp11::data_frame xy, cpp11::integers hull_in, const double concavity, const double lengthThreshold) {

  cpp11::doubles x(xy[0]);
  cpp11::doubles y(xy[1]);

   // std::vector <double> x = xy [0], y = xy [1];
    const size_t num_points = static_cast <int> (xy.nrow ());

    typedef double T;
    typedef std::array <T, 2> point_type;

    std::vector <point_type> points (num_points);
    for (auto i = 0; i < num_points; i++) {
        points[i] = { x [i], y [i] };
    }
    std::vector <int> hull;
    for (int i = 0; i < hull_in.size(); ++i) {
      hull.push_back(hull_in[i]);
    }
    auto concave_points = concaveman <T, 16> (points, hull,
            concavity, lengthThreshold);

    cpp11::writable::doubles xout (concave_points.size ()), yout (concave_points.size ());
    for (int i = 0; i < concave_points.size (); i++)
    {
        xout[i] = concave_points [i] [0];
        yout[i] = concave_points [i] [1];
    }

    cpp11::writable::data_frame res({
      "x"_nm = xout,
        "y"_nm = yout
    });

    return res;
}

