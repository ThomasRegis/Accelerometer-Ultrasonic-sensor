#include <iostream>
#include <vector>
#include <Eigen/Dense>

class CubicSplineInterpolation {
public:
    CubicSplineInterpolation(const std::vector<double>& xs, const std::vector<double>& ys);

    double interpolate(double x) const;

private:
    size_t dim_;
    std::vector<double> xs_;
    std::vector<double> ds_;  // Second derivatives
    std::vector<double> as_;
    std::vector<double> bs_;
    std::vector<double> cs_;
};

CubicSplineInterpolation::CubicSplineInterpolation(const std::vector<double>& xs, const std::vector<double>& ys) : xs_{xs}, ds_{ys} {
    dim_ = xs.size();
    Eigen::MatrixXd m = Eigen::MatrixXd::Zero(3 * dim_, 3 * dim_);
    Eigen::VectorXd v = Eigen::VectorXd::Zero(3 * dim_);

    for (size_t i = 0; i < dim_ - 1; ++i) {
        double h = xs_[i + 1] - xs_[i];
        m(3 * i, 3 * i) = h;
        m(3 * i, 3 * i + 1) = h * h;
        m(3 * i, 3 * i + 2) = h * h * h;

        m(3 * i + 1, 3 * i + 1) = 2 * h;
        m(3 * i + 1, 3 * i + 2) = 3 * h * h;

        m(3 * i + 2, 3 * i + 2) = 6 * h;

        v(3 * i) = ys_[i + 1] - ys_[i];
        v(3 * i + 1) = 0;
        v(3 * i + 2) = 0;
    }

    m(3 * (dim_ - 1), 0) = 1;
    m(3 * (dim_ - 1) + 1, 1) = 2 * (xs_[dim_ - 1] - xs_[dim_ - 2]);
    m(3 * (dim_ - 1) + 1, 2) = 3 * (xs_[dim_ - 1] - xs_[dim_ - 2]) * (xs_[dim_ - 1] - xs_[dim_ - 2]);
    v(3 * (dim_ - 1) + 1) = 6 * (ys_[0] - ys_[dim_ - 1]);

    Eigen::VectorXd u = m.fullPivHouseholderQr().solve(v);

    for (size_t i = 0; i < dim_; ++i) {
        bs_.push_back(u[3*i]);
        cs_.push_back(u[3*i + 1]);
        ds_.push_back(u[3*i + 2]);
    }
}

double CubicSplineInterpolation::interpolate(double x) const {
    size_t k = 0;
    while (k < dim_ - 1 && x > xs_[k + 1]) {
        ++k;
    }

    double h = x - xs_[k];
    return ys_[k] + bs_[k] * h + cs_[k] * h * h + ds_[k] * h * h * h;
}

int main() {
    std::vector<double> xs = {0.0, 0.16, 0.42, 0.6425, 0.8575};
    std::vector<double> ys = {100.0, 183.0, 235.0, 40.0, 15.0};

    CubicSplineInterpolation spline(xs, ys);

    // Display interpolated values for the provided xs
    for (const auto& x : xs) {
        double result = spline.interpolate(x);
        std::cout << "Interpolated value at " << x << ": " << result << std::endl;
    }

    return 0;
}
