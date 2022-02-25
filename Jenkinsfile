pipeline {
  agent any

  environment{
    UPLOAD_BASE_PATH = "${GIT_BRANCH}/${BUILD_NUMBER}"
  }

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
              "pattern": "install/LICENSE",
              "target": "playground-linux-1-mecontrol/${env.UPLOAD_BASE_PATH}/core/"
            },
            {
              "pattern": "install/include/*.h",
              "target": "playground-linux-1-mecontrol/${env.UPLOAD_BASE_PATH}/core/include/"
            },
            {
              "pattern": "install/lib/*.so.*",
              "target": "playground-linux-1-mecontrol/${env.UPLOAD_BASE_PATH}/core/lib/"
            },
          ]
        }"""
      )
      rtPublishBuildInfo (
        serverId: 'JFrogCloud'
      )
    }
  }

}
