/**
 * @file Mixture.cpp
 *
 * @brief Mixture class implementation. @see Mutation::Mixture
 */

/*
 * Copyright 2014 von Karman Institute for Fluid Dynamics (VKI)
 *
 * This file is part of MUlticomponent Thermodynamic And Transport
 * properties for IONized gases in C++ (Mutation++) software package.
 *
 * Mutation++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Mutation++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Mutation++.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "Mixture.h"
#include "StateModel.h"

namespace Mutation {

//==============================================================================

Mixture::Mixture(const MixtureOptions& options)
    : Thermodynamics::Thermodynamics(
        options.getSpeciesDescriptor(),
        options.getThermodynamicDatabase(),
        options.getStateModel()),
      Transport(
        *this,
        options.getViscosityAlgorithm(),
        options.getThermalConductivityAlgorithm(),
        options.loadTransport()),
      Kinetics(
        static_cast<const Thermodynamics&>(*this),
        options.getMechanism()),
      m_compositions(options.compositions())
{
    // Set default composition if available
    if (options.hasDefaultComposition())
        setDefaultComposition(m_compositions[options.getDefaultComposition()]);
    
    // Instatiate a new energy transfer model
    state()->initializeTransferModel(*this, *this, *this);
    
}

//==============================================================================

} // namespace Mutation
