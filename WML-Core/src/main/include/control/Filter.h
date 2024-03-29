#pragma once

// #include <frc/filters/LinearDigitalFilter.h>
#include <frc/filter/LinearFilter.h>
#include <wpi/circular_buffer.h>

#include <functional>
#include <initializer_list>
#include <utility>
#include <vector>

namespace wml {
namespace control {
  /**
   * Generic interface for a filter.
   * 
   * A filter is any mathematical construct that allows for filtering, diminishing or limiting
   * unwanted parts of a signal, be it noise, environmental effects, impulses, or otherwise.
   */
  class Filter {
   public:
    /**
     * Calculate the next output of the filter provided an input
     */
    virtual double Get(double input) = 0;
    /**
     * Reset the filter to its original state
     */
    virtual void Reset() {};
  };

  /**
   * A generic adapter to turn a function into a simple @ref Filter.
   */
  class FunctionFilter : public Filter {
   public:
    FunctionFilter(std::function<double(double)> func) : _func(func) {}

    double Get(double input) override { return _func(input); }

   private:
    std::function<double(double)> _func;
  };

  /**
   * Generic FIR / IIR filter. @ref frc::LinearDigitalFilter
   * 
   * Same implementation as the WPILib Linear Digital Filter, but using our filter interface.
   */
  class LinearFilter : public Filter {
   public:
    LinearFilter(std::initializer_list<double> gainsFF, std::initializer_list<double> gainsFB);
    LinearFilter(std::vector<double> &&ff, std::vector<double> &&fb);   // LinearFilter(std::move(ff), std::move(fb));

    double Get(double input) override;
    void Reset() override;

    static LinearFilter LowPass(double time_const, double period);
    static LinearFilter HighPass(double time_const, double period);
    static LinearFilter MovingAverage(int samples);

   private:
    wpi::circular_buffer<double> _bufferFF, _bufferFB;
    std::vector<double> _gainsFF, _gainsFB;
  };
}  // namespace control
}  // namespace wml