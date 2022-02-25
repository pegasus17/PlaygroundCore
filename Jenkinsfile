pipeline {
  agent any

  stages {
    stage("Build") {
      steps{
        cmakeBuild(
          installation: "3.22.2",
          cleanBuild: true,
          buildDir: "build",
          generator: "Ninja",
          buildType: "Debug",
          steps: [
            [args: "all"],
            [args: "install"],
            [args: "package"]
          ]
        )
      }
      post {
        success {
          dir("install") {
            archiveArtifacts(
              followSymlinks: false,
              artifacts: "**/*"
            )
          }
        }
      }
    }
  }

  post {
    success {
        rtBuildInfo(
          captureEnv: true
        )
        rtPublishBuildInfo (
          serverId: 'JFrogCloud',
          // The buildName and buildNumber below are optional. If you do not set them, the Jenkins job name is used
          // as the build name. The same goes for the build number.
          // If you choose to set custom build name and build number by adding the following buildName and
          // buildNumber properties, you should make sure that previous build steps (for example rtDownload
          // and rtIpload) have the same buildName and buildNumber set. If they don't, then these steps will not
          // be included in the build-info.
          //buildName: 'holyFrog',
          //buildNumber: '42',
          // Optional - Only if this build is associated with a project in Artifactory, set the project key as follows.
          //project: 'my-project-key'
        )
        rtUpload (
          serverId: 'JFrogCloud',
          specPath: 'config/artifactory_upload_spec.json', 
          // Optional - Associate the uploaded files with the following custom build name and build number.
          // If not set, the files will be associated with the default build name and build number (i.e the
          // the Jenkins job name and number).
          //buildName: 'holyFrog',
          //buildNumber: '42',
          // Optional - Only if this build is associated with a project in Artifactory, set the project key as follows.
          //project: 'my-project-key'
        )
    }
  }
  
}
