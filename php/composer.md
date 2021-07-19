컴포저는 php의 표준 의존성 관리 도구로 java의 maven/gradle, js의 npm등과 비슷한 관리 도구이다.

## 컴포저 장점
1.  서로다른 php프레임워크들의 확장 관리자를 통합시킴
1. 다른 사람의 라이브러리 사용가능
1. 검증된 품질 높은 컴포넌트를 골라 사용가능
1. 설치, 업데이트등 관리 자동화
1. 의존성 버저 불일치로 발생하는 문제점 해결
1. 오토로드 기능을 쉽게 사용(require지옥 탈출)

<br><br>

## coposer.json 구조
```json
{
    "name": "laravel/laravel",
    "type": "project",
    "description": "The Laravel Framework.",
    "keywords": ["framework", "laravel"],
    "license": "MIT",
    "require": {
        "php": "^7.3|^8.0",
        "fideloper/proxy": "^4.4",
        "fruitcake/laravel-cors": "^2.0",
        "guzzlehttp/guzzle": "^7.0.1",
        "laravel/framework": "^8.40",
        "laravel/tinker": "^2.5"
    },
    "require-dev": {
        "facade/ignition": "^2.5",
        "fakerphp/faker": "^1.9.1",
        "laravel/sail": "^1.0.1",
        "mockery/mockery": "^1.4.2",
        "nunomaduro/collision": "^5.0",
        "phpunit/phpunit": "^9.3.3"
    },
    "autoload": {
        "psr-4": {
            "App\\": "app/",
            "Database\\Factories\\": "database/factories/",
            "Database\\Seeders\\": "database/seeders/"
        }
    },
    "autoload-dev": {
        "psr-4": {
            "Tests\\": "tests/"
        }
    },
    "scripts": {
        "post-autoload-dump": [
            "Illuminate\\Foundation\\ComposerScripts::postAutoloadDump",
            "@php artisan package:discover --ansi"
        ],
        "post-root-package-install": [
            "@php -r \"file_exists('.env') || copy('.env.example', '.env');\""
        ],
        "post-create-project-cmd": [
            "@php artisan key:generate --ansi"
        ]
    }
}
```
- require : 프로젝트가 의존하는 컴포넌트 목록
    -  "laravel/framework": "^8.40.*" : laravel은 벤더 이름, framework는 패키지 이름이고 둘을 합쳐서 컴포넌트 이름이라고 한다. 