pipeline {
  agent any

  environment{
    JFROG_SERVER = "JFrogCloud"
    JFROG_REPO = "mecontrol-playground-develop"
    UPLOAD_BASE_PATH = "jenkins/core-${GIT_BRANCH}/${BUILD_NUMBER}"
    // jenkins/core-develop/2/core-linux-sources.zip
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
        cmakeBuild (
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
            archiveArtifacts (
              followSymlinks: false,
              artifacts: "**/*"
            )
          }
          zip (
            zipFile: "package/core-linux-sources.zip",
            archive: true,
            overwrite: true,
            dir: '.',
            exclude: '',
            glob: ''
          )
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
              "pattern": "package/.+-.+-.+.zip",
              "target": "${JFROG_REPO}/${env.UPLOAD_BASE_PATH}/"
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
