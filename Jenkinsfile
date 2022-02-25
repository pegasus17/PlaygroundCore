pipeline {
  agent any

  environment{
    MODULE_NAME = "core"
    BUILD_PATH = "build"
    INSTALL_PATH = "${BUILD_PATH}/install"
    PACKAGE_PATH = "${BUILD_PATH}/package"

    JFROG_SERVER = "JFrogCloud"
    JFROG_REPO = "mecontrol-playground-develop"
    UPLOAD_BASE_PATH = "jenkins/${MODULE_NAME}-${GIT_BRANCH}/${BUILD_NUMBER}" 
  }

  stages {
    stage("Preparation") {
      steps {
        rtBuildInfo (
          captureEnv: true,          
          // Optional - Also delete the build artifacts when deleting a build.
          deleteBuildArtifacts: true
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
          buildDir: "${BUILD_PATH}",
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
          zip (
            zipFile: "${PACKAGE_PATH}/${MODULE_NAME}-linux-package.zip",
            archive: true,
            overwrite: true,
            dir: "${INSTALL_PATH}",
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
              "pattern": "${PACKAGE_PATH}/${MODULE_NAME}-*-*.zip",
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
