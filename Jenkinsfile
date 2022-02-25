pipeline {
  agent any

  environment{
    JFROG_SERVER = "JFrogCloud"
    JFROG_REPO = "mecontrol-playground-${GIT_BRANCH}"
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
        serverId: "${JFROG_SERVER}",
        failNoOp: true,
        spec: """{
          "files": [
            {
              "pattern": "install/LICENSE",
              "target": "${JFROG_REPO}/${env.UPLOAD_BASE_PATH}/core/"
            },
            {
              "pattern": "install/include/*.h",
              "target": "${JFROG_REPO}/${env.UPLOAD_BASE_PATH}/core/include/"
            },
            {
              "pattern": "install/lib/*.so.*",
              "target": "${JFROG_REPO}/${env.UPLOAD_BASE_PATH}/core/lib/"
            }
          ]
        }"""
      )
      rtPublishBuildInfo (
        serverId: "${JFROG_SERVER}"
      )
    }
  }

}
