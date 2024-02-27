/* 맨 위로 버튼 : 스크롤 쫓아가기 */
$(document).ready(function(){
    var currentPosition = parseInt($("#goToTop").css("top"));
    $(window).scroll(function() {
        var position = $(window).scrollTop(); 
        $("#goToTop").stop().animate({"top":position+currentPosition+"px"},300);
    });
    });

    $("#goToTop > a").click(function () {
        window.scrollTo(0, 0);
    })

$(".subject > li > div > img").mouseover(function(){      //이미지에 손 올리면 커서 모양
    $(this).css("cursor","pointer");
})

$(".subject > li > div > img").click(function(){          //이미지 클릭시 문서 가져와
    event.preventDefault();
    location.href = $(this).closest("div").next().find("a").attr("href");
})

/* html값으로 검색하는 함수 */
$(".relate").click(function () {
    event.preventDefault();
    window.open("https://www.google.com/search?q=" + $(this).html(), '_blank');
    
});

$(".search>button").click(function () {
    event.preventDefault();
    window.open("https://www.google.com/search?q=" + $(".search > input").val(), '_blank');
    $(".search>input").val("");
});



//상단바 드르륵 함수
$(document).ready(function() {
//마우스 진입하는 경우
$(".gnb .m").mouseenter(function() {
    $(this).addClass("on"); //클래스 추가
    $(this).find(".menu").slideDown();
});
//마우스 떠나는 경우
$(".gnb .m").mouseleave(function() {
    $(this).removeClass("on"); //클래스 삭제
    $(this).find(".menu").css("display", "none");
});
});

$(document).ready(function() {
    // 모든 .base 클래스를 가진 요소에 대해 루프를 돌음
    $(".base").each(function() {
        // 현재 요소에서 .evalue 클래스를 가진 p 태그의 내용을 가져옴
        var ratingValue = parseFloat($(this).find(".evalue").text());

        // 현재 요소에서 #star1의 width를 설정
        $(this).find("#star1").css("width", ratingValue * 10 + "%");
    });
});