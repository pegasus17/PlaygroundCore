pipeline{
  agent any
  stages{
    stage("Build"){
      steps{
          cmakeBuild(
            installation: '3.22.2',
            cleanBuild: true,
            buildDir: 'build',
            generator: 'Ninja',
            buildType: 'Debug',
            steps: [
                [args: 'all'],
                [args: 'install']
            ]
          )
      }
      post {
        success {
          archiveArtifacts(
            followSymlinks: false,            
            artifacts: 'install/.*')
        }
      }
    }
  }
}
