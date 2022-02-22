pipeline{
  agent any
  stages{
    stage("Build"){
      steps{
        cmakeBuild(
          installation: "3.22.2",
          cleanBuild: true,
          buildDir: "build",
          generator: "Ninja",
          buildType: "Debug",
          steps: [
            [args: "all"],
            [args: "install"]
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

    stage("Artifactory Upload") {
      steps
      {
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
}
