/*
 * Projection.h
 *
 * Holding area for universal projection information.  All projection objects should be retrieved using these functions.
 *
 * Copyright (c) 2011-2016 United States Government as represented by
 * the National Aeronautics and Space Administration.  No copyright
 * is claimed in the United States under Title 17, U.S.Code. All Other
 * Rights Reserved.
 */

#ifndef PROJECTION_H_
#define PROJECTION_H_

#include "EuclideanProjection.h"
#include "LatLonAlt.h"
#include <string>

 /*
  * WARNING! The string "EuclideanProjection" is the name of a MACRO
  * representing the actual type of the chosen projection.
  *
  * Anything starting with this string will be replaced with SOMETHING
  * ELSE at compile time.  You may not notice a difference.  At first.
  *
  */

 namespace larcfm {

/**
 * A static holding class for universal projection information.  All projection objects should be retrieved from this class.
 */
class Projection {
   private:
	   static EuclideanProjection projection;
	   static ProjectionType ptype;
   public:
	   /**
	    * Returns a new projection for the current type with the given reference point.
	    */
	   static EuclideanProjection createProjection(double lat, double lon, double alt);
	   /**
	    * Returns a new projection for the current type with the given reference point.
	    */
	   static EuclideanProjection createProjection(const LatLonAlt& lla);

	   /**
	    * Returns a new projection for the current type with the given reference point.
	    * This will return an altitude-preserving projection against the given Position if it is lat/lon.
	    * If it is Euclidean, the projection will be against the LatLonAlt.ZERO point.
	    */
	  static EuclideanProjection createProjection(const Position& pos);

	  /**
	   * Geodetic projections into the Euclidean frame, for various reasons, tend to lose accuracy over long distances
	   * or when close to the poles.  This can be countered by examining trajectories as shorter segments at a time.  
	   * This is already done in Detector and Stratway, but not in any other tools.  For CDII, it is best
	   * to break up the ownship's plan in this way.  For CDSI and IntentBands, it is better to break up the traffic
	   * in this way.
	   * 
	   * This return an estimate on the suggested maximum segment size, depending on the current projection.
	   * 
	   * @param lat - latitude  [rad]
	   * @param accuracy - desired accuracy (allowable error) [m]
	   * @return the maximum length of a trajectory segment at the given latitude that preserves the desired accuracy.
	   */
	   static double projectionConflictRange(double lat, double accuracy);

	  /**
	   * This is a range about which the projection will completely break down and start producing nonsensical answers.
	   * Attempting to use the projection at ranges greater than this is an error state (at ranges less than this but greater
	   * than the conflictRange, it may still be unacceptably inaccurate, however).
	   * 
	   * @return maximum range for the projection (in meters).	
	   */
	   static double projectionMaxRange();


	   /**
	    * Set the projection to a new type.  This is a global change.
	    */
	   static void setProjectionType(ProjectionType t);

	   /**
	    * Given a string representation of a ProjectionType, return the ProjectionType
	    */
	   static ProjectionType getProjectionTypeFromString(std::string s);

	   /**
	    * Return the current ProjectionType
	    */
	   static ProjectionType getProjectionType();
   };


   /**
    * \deprecated {Use Projection:: version.}
    * Returns a new projection for the current type with the given reference point.
    */
   EuclideanProjection getProjection(double lat, double lon, double alt);
   /**
    * \deprecated {Use Projection:: version.}
    * Returns a new projection for the current type with the given reference point.
    */
   EuclideanProjection getProjection(const LatLonAlt& lla);

   /**
    * \deprecated {Use Projection:: version.}
    * Geodetic projections into the Euclidean frame, for various reasons, tend to lose accuracy over long distances
    * or when close to the poles.  This can be countered by examining shorter segments at a time.  
    * This is already done in Detector and Stratway, but not in any other tools.  For CDII, it is best
    * to break up the ownship's plan in this way.  For CDSI and IntentBands, it is better to break up the traffic
    * in this way.
    * 
    * This return an estimate on the suggested maximum segment size, depending on the current projection.
    * 
    * @param lat - latitude  [radians]
    * @param accuracy - desired accuracy (allowable error) [m]
    * @return the maximum length of a trajectory segment at the given latitude that preserves the desired accuracy.
    */
   double projectionConflictRange(double lat, double accuracy);

   /**
    * \deprecated {Use Projection:: version.}
    * This is a range about which the projection will completely break down and start producing nonsensical answers.
    * Attempting to use the projection at ranges greater than this is an error state (at ranges less than this but greater
    * than the conflictRange, it may still be unacceptably inaccurate, however).
    * 
    * @return maximum range for the projection
    */
   double projectionMaxRange();
     

   /**
    * \deprecated {Use Projection:: version.}
    * Set the projection to a new type.  This is a global change.
    */
   void setProjectionType(ProjectionType t);

   /**
    * \deprecated {Use Projection:: version.}
    * Given a string representation of a ProjectionType, return the ProjectionType
    */
   ProjectionType getProjectionTypeFromString(std::string s);

   /**
    * \deprecated {Use Projection:: version.}
    * Return the current ProjectionType
    */
   ProjectionType getProjectionType();

 }
 
#endif /* PROJECTION_H_ */
