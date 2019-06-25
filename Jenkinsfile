REPO_NAME = env.JOB_NAME.split('/')[1]
PKG_NAME  = REPO_NAME.substring(0, REPO_NAME.length() - 4)
node ('master') {
    stage ('Checkout') {
        checkoutSubmodule()
        dir (PKG_NAME) {
            stash name: 'checkout', include: '*/**'
        }
    }

    stage ('Pre-commit Checks') {
        REPO_NAME = env.JOB_NAME.split('/')[1]
        PKG_NAME  = REPO_NAME.substring(0, REPO_NAME.length() - 4)
        dir(PKG_NAME) {
            preCommit()
        }
    }
}
stage ('Build') {
    node ('rpi-cross-compile') {
        sh "sudo rm -rf *"
        unstash 'checkout'

        mountCrossCompilerImage()

        sh 'sudo --preserve-env su --preserve-environment -c "$WORKSPACE/cross-compiled-build.sh"'

        dir ('/mnt/tmp/') {
            stash includes: "lxde-pt-shutdown-helper", name: 'build', useDefaultExcludes: false
        }
    }
}
node ('master') {
    stage ('Package') {
        dir(PKG_NAME) {
            unstash 'build'
        }
        env.DEB_BUILD_OPTIONS="nostrip"
        buildGenericPkg(false, PKG_NAME)

        try {
            lintian()
        } catch (e) {
            currentBuild.result = 'UNSTABLE'
        }
    }

    stage ('Publish') {
        publishSirius()
    }
}
