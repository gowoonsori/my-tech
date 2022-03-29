## 긴 함수
함수가 길면 이해하기 어렵고, 함수가 짧을 수록 문맥 전환을 필요로 하기에 많은 오버헤드가 존재하지면 컴퓨터 성능/기술의 많은 발전

### 임시 변수를 질의 함수로 바꾸기
- 임시 변수를 함수로 추출하여 분리하면 함수로 전달해야 할 매개변수를 줄일 수 있다.
  
```java
// ASIS
public void writeMarkDown(){
  //생략...

  foreach(Participants p : participants) {
    long count = p.homework().values().stream().filter(v -> v).count();
    double rate = count * 100 / totalNumberOfEvents;

    String markdownForHomework = getMarkdownForParticipant(totalNumberOfEvents,p,rate);
    writer.print(markdownForHomework);
  }
}

private String getMarkDownForParticipant(int totalNumberOfEvents, Participant p, double rate) {
  return String.format("| %s %s | %.2f%% |\n", p.username(), checkMark(p,totalNumberOfEvents), rate)
}

//ToBe
public void writeMarkDown(){
  //생략...

  foreach(Participants p : participants) {
    String markdownForHomework = getMarkdownForParticipant(totalNumberOfEvents,p);
    writer.print(markdownForHomework);
  }
}

private String getMarkDownForParticipant(int totalNumberOfEvents, Participant p) {
  return String.format("| %s %s | %.2f%% |\n", p.username(), checkMark(p,totalNumberOfEvents), getRate(totalNumberOfEvents,p)))
}

private double getRate(int totalNumberOfEvents, Participant p) {
  long count = p.homework().values().stream().filter(v -> v).count();
  return count * 100 / totalNumberOfEvents;
}
```

### 매개변수 객체 만들기
같은 매개변수들이 여러 메소드에 걸쳐 나타난다면 그 매개변수들을 묶은 자료구조로 만들기

- 데이터간의 관계를 보다 명시적으로 표현 가능
- 함수에 전달할 매개변수 개수를 줄일 수 있다.
- 도메인을 이해하는데 중요한 역할을 하는 클래스로 발전 할 수 있다. 

네이밍부분에서 언급했던 Record 자료구조를 사용하거나 별도의 object를 정의해서 사용

### 객체 통째로 넘기기
- 매개변수 목록을 줄이고 후에 추가할지도 모를 매개변수도 줄일 수 있다.
- 적용하기 전에 의존성을 고려
  - 해당 함수가 다른 곳에서 사용할 여지가 있는가? 있다면 객체에 의존하기보다 특정 데이터들로 놔두는게 더 나을 수도 있다.
- 어쩌면, 해당 메소드의 위치가 적절하지 않을 수 있다.
  - 문맥상 메소드의 위치가 Service가 아니라 domain자체에 들어있는게 더 적합할 수도 있다.

### 함수를 명령으로 바꾸기
- 함수를 독립적인 객체인 Command 로 만들어 사용 (커맨드 패턴)
- 장점
  - 복잡한 기능을 구현하는데 필요한 여러 메소드로 추가할 수 있다.
  - 상속이나 템플릿 활용
  - 복잡한 메소드를 여러 메소드나 필드를 활용해 쪼갤 수 있다.
- 대부분의 경우에는 **커맨드** 보다는 **함수**를 사용
  - 요즘 Modern한 언어들 대부분은 함수를 값으로 사용이 가능하기 때문에 별도의 커맨드 패턴이 불필요

### 조건문 분해하기
여러 조건에 따라 달라지는 코드를 작성하다보면 함수가 길어지는데 **조건**과 **액션** 모두 **의도**를 표현해야 한다.

기술적으로는 `중복 코드의 함수추출하기`와 같으나 목적만 다르다.

```java
//AsIs
private Participant findParticipant(String username, List<Participant> participants) {
    Participant participant = null;
    if (participants.stream().noneMatch(p -> p.username().equals(username))) {
        particiapnt = new Participant(username);
        participants.add(participant);
    } else {
        participant = participants.stream().filter(p -> p.username().equals(username)).findFirst().orElseThrow();
    }
    return participant;
}

//ToBe
private Participant findParticipant(String username, List<Participant> participants) {
    return isNewParticipant(username,participants) ? 
            createParticipant(username,participants) : 
            findExistingParticipant(username, participants);
}

private boolean isNewParticipant(String username, List<Participant> participants) {
    return participants.stream().noneMatch(p -> p.username().equals(username));
}

private Participant createNewParticipant(String username, List<Participant> participants) {
    Participant particiapnt = new Participant(username);
    participants.add(participant);
    return participant;
}

private Participant findExistingParticipant(String username, List<Participant> participants) {
    return participants.stream().filter(p -> p.username().equals(username)).findFirst().orElseThrow();
}
```

### 반복문 쪼개기
성능적으로 보나 효율적인 면에서 하나의 반복문에서 여러 다른 작업을 하는 코드를 작성하게 된다.

성능적인 부분이 병목현상을 일으키는 것이 아니라면, 반복문을 여러개로 쪼개는 것이 쉽게 이해하고 수정이 쉬워 지기 때문에, 일단 리팩토링을 한 후 성능 이슈가 생길때 최적화를 시도하는 것이 더 좋을 수 있다. 

>시간복잡도가 N인 반복문을 몇번돌아도 O(N) 이다.

```java
//AsIs
//하나의 issue를 조회하는 for문 안에 댓글 작성자 정보조회하는 로직과 첫번째 참석자 조회하는 로직 존재
private void print() {
    GitHub github = GitHub.connect();
    GHRepository repository = github.getRepository("gowoonsori/example");
    List<Participant> participants = new CopyOnWriteArrayList<>();

    int totalNumberOfEvents = 15;
    ExecutorService service = Executors.newFixedTrheadPool(8);
    CountDownLatch latch = new CountDownLatch(totalNumberOfEvents); //15개의 스레드를 돌기 위한 count 값

    //지정된 갯수만큼의 issue 조회할 예정
    for (int index = 1; index <= totalNumberOfEvents; index++) {
        int eventId = index;
        service.execute(() -> {
            try {
                //github api이용해 issue조회
                GHIssue issue = repository.getIssue(eventId);
                //issue의 댓글들 조회
                List<GHIssueComment> comments = issue.getComments();

                //댓글들의 정보와 첫번째 작성자 조회
                Date firstCreatedAt = null;
                Participant first = null;
                for(GHIssueComment comment : comments){
                    //댓글 작성자 정보 조회
                    Participant participant = findParticipant(comment.getUserName(), participants);
                    //댓글 작성자 참석 여부 표시 (reaction add)
                    participant.setHomeworkDone(eventId);

                    //첫번째 댓글 작성자 조회
                    if(firstCreatedAt == null || comment.getCreatedAt().before(firstCreatedAt)) {
                        firstCreatedAt = comment.getCreatedAt();
                        first = participant;
                    }
                }
                //첫번째 댓글 작성자 표시
                firstParticipantsForEachEvent[eventId - 1] = first;
                latch.countDown();
            } catch (IOException e) {
                throw new IllegalArgumentException(e);
            }
        });
    }

    latch.await();
    service.shutdown();

    new StudyPrinter(this.totalNumberOfEvents, this.participants).execute();
    Arrays.stream(this.firstParticipantsForEachEvent).forEach(p -> System.out.println(p.username));
}

//ToBe
private final int totalNumberOfEvents;
private final List<Participant> participants;
private final Participant[] firstParticipantForEachEvent;

private void print() {
    checkGithubIssues(getGhRepository());   
    new StudyPrinter(this.totalNumberOfEvents, this.participants).execute();
    printFirstParticipants();
}

private void checkGithubIssues(GHRepository repository) {
    ExecutorService service = Executors.newFixedTrheadPool(8);
    CountDownLatch latch = new CountDownLatch(totalNumberOfEvents);

    //issues 조회
    for (int index = 1; index <= this.totalNumberOfEvents; index++) {
        int eventId = index;
        service.execute(() -> {
            try {
                GHIssue issue = repository.getIssue(eventId);
                List<GHIssueComment> comments = issue.getComments();
                checkHomework(comments, participants,eventId);      //참석 여부 확인
                firstParticipantsForEachEvent[eventId-1] = findFirst(comments,participants);    //첫번째 작성자 조회
                latch.countDown();
            } catch (IOException e) {
                throw new IllegalArgumentException(e);
            }
        });
    }

    latch.await();
    service.shutdown();

}

private void checkHomework(List<GHIssueComment> comments, List<Participant> participants, int eventId) {
    for(GHIssueComment comment : comments){
        Participant participant = findParticipant(comment.getUserName(), participants);
        participant.setHomeworkDone(eventId);
    }
}

private void findFirst(List<GHIssueComment> comments, List<Participant> participants) {
    Date firstCreatedAt = null;
    Participant first = null;
    for(GHIssueComment comment : comments){
        Participant participant = findParticipant(comment.getUserName(), participants);

        if(firstCreatedAt == null || comment.getCreatedAt().before(firstCreatedAt)) {
            firstCreatedAt = comment.getCreatedAt();
            first = participant;
        }
    }
}

private void printFirstParticipants() {
    Arrays.stream(this.firstParticipantsForEachEvent).forEach(p -> System.out.println(p.username));
}
```

### 조건문을 다형성으로 바꾸기
true/false 가 아닌 switch문이나 if문에서 특수한 타입에 따라서 다른 로직으로 처리해야 하는 경우에 다형성을 적용하면 명확하게 분리할 수 있다.

- 공통으로 사용되는 로직은 상위클래스에 두고 달라지는 부분만 하위클래스에 둠으로써, 달라지는 부분만 강조
- 모든 조건문을 다형성으로 바꿔야 하는 것이 아니라 정말 복잡한 케이스의 경우에만 적용될 수 있는 가능성이 있다는 것

```java
//AsIs
public class StudyPrinter {
    //프로퍼티, 생성자, 메서드들 생략 ...

    private void print() {
        switch(printMode) {
            case CVS -> {
                try (FileWirter fileWriter = new FileWriter("participants.cvs");
                    PrintWriter writer = new PrintWriter(fileWriter)) {
                    
                    writer.println(cvsHeader(this.participants.size()));
                    this.pariticipants.forEach(p -> writer.println(getCvsForParticipant(p)));
                }
            }
            case CONSOLE -> {
                this.participants.forEach(p -> System.out.printf("%s %s:%s\n", p.username(), checkMark(p), p.getRate(this.totalNumberOfEvents())));
            }
            case MARKDOWN -> {
            try (FileWirter fileWriter = new FileWriter("participants.md");
                    PrintWriter writer = new PrintWriter(fileWriter)) {
                    
                    writer.print(header(this.participants.size()));
                    this.pariticipants.forEach(p -> writer.print(getMarkdownForParticipant(p))));
                }  
            }
        }
    }
}

//ToBe
public abstract class StudyPrinter {
    //프로퍼티, 생성자, 메서드들 생략 ...

    private abstract void print(); 
}

public class ConsolePrinter extends StudyPrinter {
    //생성자 생략

    @Override
    public print() {
        try (FileWirter fileWriter = new FileWriter("participants.cvs");
              PrintWriter writer = new PrintWriter(fileWriter)) {
                    
            writer.println(cvsHeader(this.participants.size()));
            this.pariticipants.forEach(p -> writer.println(getCvsForParticipant(p)));
        }
    }
}

public class CvsPrinter extends StudyPrinter {
    //생성자 생략

    @Override
    public print() {
        this.participants.forEach(p -> System.out.printf("%s %s:%s\n", p.username(), checkMark(p), p.getRate(this.totalNumberOfEvents())));
    }
}

public class MarkdownPrinter extends StudyPrinter {
    //생성자 생략

    @Override
    public print() {
        try (FileWirter fileWriter = new FileWriter("participants.md");
              PrintWriter writer = new PrintWriter(fileWriter)) {
                    
            writer.print(header(this.participants.size()));
            this.pariticipants.forEach(p -> writer.print(getMarkdownForParticipant(p))));
        }  
    }
    }
}
```