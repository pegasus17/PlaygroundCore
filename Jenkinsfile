pipeline {
  agent any

  stages {
    stage("Preperation") {
      steps {
        rtBuildInfo (captureEnv: true)
      }
    }

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
        rtUpload (serverId: 'JFrogCloud', specPath: 'config/artifactory_upload_spec.json')
        rtPublishBuildInfo (serverId: 'JFrogCloud' )
    }
  }

}
