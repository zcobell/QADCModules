#ifndef HARMONICSOUTPUT_H
#define HARMONICSOUTPUT_H

#include <string>
#include "adcircmodules_global.h"
#include "harmonicsrecord.h"

class HarmonicsOutputImpl;

namespace Adcirc {
namespace Harmonics {

/**
 * @class HarmonicsOutput
 * @author Zachary Cobell
 * @copyright Copyright 2018 Zachary Cobell. All Rights Reserved. This project
 * is released under the terms of the GNU General Public License v3
 * @brief The HarmonicsOutput class handles the reading/writing of ADCIRC
 * harmonics files
 *
 */

class HarmonicsOutput {
 public:
  ADCIRCMODULES_EXPORT HarmonicsOutput(
      const std::string& filename = std::string(), bool velocity = false);

  ADCIRCMODULES_EXPORT ~HarmonicsOutput();

  void ADCIRCMODULES_EXPORT read();

  void ADCIRCMODULES_EXPORT write(const std::string& filename);

  std::string ADCIRCMODULES_EXPORT filename() const;
  void ADCIRCMODULES_EXPORT setFilename(const std::string& filename);

  size_t ADCIRCMODULES_EXPORT index(const std::string& name);

  std::string ADCIRCMODULES_EXPORT name(size_t index);

  //...fort.53 type parameters
  Adcirc::Harmonics::HarmonicsRecord ADCIRCMODULES_EXPORT* amplitude(
      const std::string& name);

  Adcirc::Harmonics::HarmonicsRecord ADCIRCMODULES_EXPORT* amplitude(
      size_t index);

  Adcirc::Harmonics::HarmonicsRecord ADCIRCMODULES_EXPORT* phase(
      const std::string& name);

  Adcirc::Harmonics::HarmonicsRecord ADCIRCMODULES_EXPORT* phase(size_t index);

  //...fort.54 type parameters
  Adcirc::Harmonics::HarmonicsRecord ADCIRCMODULES_EXPORT* u_magnitude(
      const std::string& name);

  Adcirc::Harmonics::HarmonicsRecord ADCIRCMODULES_EXPORT* u_magnitude(
      size_t index);

  Adcirc::Harmonics::HarmonicsRecord ADCIRCMODULES_EXPORT* u_phase(
      const std::string& name);

  Adcirc::Harmonics::HarmonicsRecord ADCIRCMODULES_EXPORT* u_phase(
      size_t index);

  Adcirc::Harmonics::HarmonicsRecord ADCIRCMODULES_EXPORT* v_magnitude(
      const std::string& name);

  Adcirc::Harmonics::HarmonicsRecord ADCIRCMODULES_EXPORT* v_magnitude(
      size_t index);

  Adcirc::Harmonics::HarmonicsRecord ADCIRCMODULES_EXPORT* v_phase(
      const std::string& name);

  Adcirc::Harmonics::HarmonicsRecord ADCIRCMODULES_EXPORT* v_phase(
      size_t index);

  size_t ADCIRCMODULES_EXPORT numConstituents() const;

  void ADCIRCMODULES_EXPORT setNumConstituents(const size_t& numConstituents);

  size_t ADCIRCMODULES_EXPORT numNodes() const;

  void ADCIRCMODULES_EXPORT setNumNodes(const size_t& numNodes);

  bool ADCIRCMODULES_EXPORT isVelocity() const;

  size_t ADCIRCMODULES_EXPORT nodeIdToArrayIndex(size_t id);

  int ADCIRCMODULES_EXPORT filetype() const;

 private:
  HarmonicsOutputImpl* m_impl;
};
}  // namespace Harmonics
}  // namespace Adcirc

#endif  // HARMONICSOUTPUT_H
