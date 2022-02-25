pipeline {
  agent any

  stages {
    stage("Preparation") {
      steps {
        rtBuildInfo (
          captureEnv: true,          
          // Optional - Also delete the build artifacts when deleting a build.
          deleteBuildArtifacts: true,
        )

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
      rtUpload (
        serverId: 'JFrogCloud',
        failNoOp: true,
        spec: """{
          "files": [
            {
              "pattern": "install/*.*",
              "target": "playground-linux-1-mecontrol/${env.GIT_BRANCH}/core/"
            }
          ]
        }"""
      )
      rtPublishBuildInfo (
        serverId: 'JFrogCloud'
      )
    }
  }

}
