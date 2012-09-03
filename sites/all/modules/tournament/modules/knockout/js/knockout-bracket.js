(function ($) {
  Drupal.behaviors.knockoutBracket = {
    attach: function (context, settings) {
      $('#knockout-bracket-wrapper', context).once('knockout-bracket', function () {
        // Add drag scrolling
        $('#knockout-bracket-wrapper').dragscrollable({dragSelector: '#knockout-bracket'});

        // Drag cursors
        $('#knockout-bracket')
        .mousedown(function() {
          $(this).addClass('grabbing');
        })
        .mouseup(function() {
          $(this).removeClass('grabbing');
        });

        // Space out bottom participant to reveal match links below
        $('#tournament-knockout .match.node').hover(
          function() {
            $(this).css({
              marginBottom : function(index, value) {
                return parseInt(value) - 10;
              }
            });
          },
          function() {
            $(this).css({
              marginBottom : function(index, value) {
                return parseInt(value) + 10;
              }
            });
          }
        );

        // Participant highlighting
        $('#tournament-knockout .participant').hover(
          function() {
            var id = $(this).attr('participant-id');
            if (id != '0') {
              $(".participant-" + id).addClass('hover');
            }
          },
          function() {
            var id = $(this).attr('participant-id');
            if (id != '0') {
              $(".participant-" + id).removeClass('hover');
            }
          }
        );

        // Toggle knockout tabs
        $('#knockout-bracket-tabs a').click(function() {
          var location = $(this).attr('location');

          // Set the tab active
          $('#knockout-bracket-tabs a').removeClass('active');
          $(this).addClass('active');

          // Set the tab contents active
          $('div.knockout-bracket-pane').removeClass('active');
          $('div.knockout-bracket-pane.' + location).addClass('active');
          return false;
        });

        // Link action
        $('#knockout-bracket-actions .bracket-link a').click(function() {
          var selector = $('#knockout-bracket-link');
          selector.toggle();

          $(this).toggleClass('clicked');

          // Ensure clicks outside of the menu hide it
          $('#knockout-bracket').mousedown(function(event) {
            var target = $(event.target);
            if (target.parents('#knockout-bracket-link').length == 0) {
              selector.hide().removeClass('clicked');
            }
          });

          return false;
        });

        // Link textfields
        $('#knockout-bracket-link .form-text').click(function() {
          $(this).select();
        });
      });
    }
  };
})(jQuery);
