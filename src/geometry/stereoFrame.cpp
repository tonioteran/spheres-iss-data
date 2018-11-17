/**
 * @file stereoFrame.cpp
 * @brief shows VERTIGO left camera frame wrt SPH fixed body frame
 * @date November 16, 2018
 * @author Antonio Terán, teran@mit.edu
 */

#include <iostream>

#include <boost/thread/thread.hpp>
#include <Eigen/Dense>
#include <pcl/visualization/pcl_visualizer.h>

bool g_nextIteration = false;

void keyboardEventOccurred(const pcl::visualization::KeyboardEvent& event,
    void* nothing){
  if (event.getKeySym () == "space" && event.keyDown ())
    g_nextIteration = true;
}// keyboardEventOccurred

int main() {

  std::cout << "\n Visualizing stereo camera frame \n";

  /* create the viewer */
  boost::shared_ptr<pcl::visualization::PCLVisualizer> 
      viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
  viewer->setBackgroundColor(0,0,0); /*dark*/
  viewer->addCoordinateSystem(0.103); /*sph radius apprx*/
  viewer->initCameraParameters();

  /* SPH body-fixed frame B to left stereo cam frame C pose */
  Eigen::Transform<float, 3, Eigen::Affine> PBtoC = 
            Eigen::Transform<float, 3, Eigen::Affine>::Identity();
  PBtoC.translate( Eigen::Vector3f(0.234-0.025, 0.045, 0.030) );
  PBtoC.rotate( (Eigen::Matrix3f() <<  0,  0,  1,
                                      -1,  0,  0,
                                       0, -1,  0).finished() );
  viewer->addCoordinateSystem(0.05, PBtoC, "PBtoC", 0);
  /* add CCD plane */
  pcl::ModelCoefficients stereoLeftCCDcoeffs; /* ax + by + cz + d = 0 */
  stereoLeftCCDcoeffs.values.push_back(1.0); /* a */
  stereoLeftCCDcoeffs.values.push_back(0.0); /* b */
  stereoLeftCCDcoeffs.values.push_back(0.0); /* c */
  stereoLeftCCDcoeffs.values.push_back(0.0); /* d */
  viewer->addPlane(stereoLeftCCDcoeffs, 0.234-0.025, 0.045, 0.03, "leftStereoCCD");

  /* register keyboard callback */
  viewer->registerKeyboardCallback(&keyboardEventOccurred, (void*) NULL);
  
  while (!viewer->wasStopped()) {

    viewer->spinOnce(100);
    boost::this_thread::sleep(boost::posix_time::microseconds(100000));

    if (g_nextIteration) {
      g_nextIteration = false;
    }

  }/*while*/

}/*main*/
