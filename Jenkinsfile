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

      dsCreateReleaseBundle(
        serverId: "${JFROG_SERVER}",
        name: "example-release-bundle",
        version: "${BUILD_NUMBER}",
        spec: """{
          "files": [{
            "pattern": "${PACKAGE_PATH}/${MODULE_NAME}-*-*.zip"
          }]
        }""",
        // The default is "plain_text". The syntax for the release notes. Can be one of 'markdown', 'asciidoc', or 'plain_text'.
        releaseNotesSyntax: "markdown",
        // Optional. If set to true, automatically signs the release bundle version.
        signImmediately: true,
        // Optional. Path to a file describing the release notes for the release bundle version.
        //releaseNotesPath: "path/to/release-notes",
        // Optional. The passphrase for the signing key.
        //gpgPassphrase: "abc",
        // Optional. A repository name at the source Artifactory instance, to store release bundle artifacts in. If not provided, Artifactory will use the default one.
        //storingRepo: "release-bundles-1",
        // Optional.
        //description: "Some desc",
        // Optional. Path to a file with the File Spec content.
        //specPath: "path/to/filespec.json",
        // Optional. Set to true to disable communication with JFrog Distribution.
        dryRun: true
      )

      rtPublishBuildInfo (
        serverId: "${JFROG_SERVER}"
      )
    }
  }

}
