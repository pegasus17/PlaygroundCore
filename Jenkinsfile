pipeline {
  agent any

  environment{
    JFROG_SERVER = "JFrogCloud"
    JFROG_REPO = "mecontrol-playground-develop"
    UPLOAD_BASE_PATH = "jenkins/core-${GIT_BRANCH}/${BUILD_NUMBER}"
    // jenkins/core-develop/2/core-linux-sources.zip

    BUILD_PATH = "build"
    INSTALL_PATH = "${BUILD_PATH}/install"
    PACKAGE_PATH = "${BUILD_PATH}/package"
  }

  stages {
    stage("Preparation") {
      steps {
        rtBuildInfo (
          captureEnv: true,          
          // Optional - Also delete the build artifacts when deleting a build.
          deleteBuildArtifacts: true,
        )
        dir("${BUILD_PATH}")
        {
          deleteDir()
        }

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
          dir("${BUILD_INSTALL_PATH}") {
            archiveArtifacts (
              followSymlinks: false,
              artifacts: "**/*"
            )
          }
          zip (
            zipFile: "${PACKAGE_PATH}/core-linux-sources.zip",
            archive: true,
            overwrite: true,
            dir: "${BUILD_INSTALL_PATH}",
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
              "pattern": "${PACKAGE_PATH}/core-*-*.zip",
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
