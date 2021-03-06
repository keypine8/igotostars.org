/* this is futhtm.h */

// MIT License
//
// Copyright (c) 2017 softwaredev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

char my_aspect_text[512];

struct aspect {
  char *asp_code;
  char *asp_text;
} f_asptab[] = {
  {"mabju", "It's best to look in the pool first to see if there's any water there before you try your fancy double flip off the diving board.  Take it easy.  Expansion and over-optimism can lead to unwise actions."},
  {"mabne", "Your activities can be badly affected by confusion about what's important and what's not.  Avoid secret activities during this time and watch out for deception in business."},
  {"mabpl", "Serious power struggles can cause a lot of trouble.  Control the temper.  This is also a time for extra caution in physical things like driving a car."},
  {"mabsa", "Your actions at this time are under frustrating influences.  You get incredible delays when you're ready to go, so be careful not to allow your impatience to cause accidents."},
  {"mabur", "You could do reckless and dangerous things upon sudden stupid impulses.  Just try to hold the temper and take it easy during this time."},

  {"macju", "Your energy is expanded.  Now's the time to start dynamic actions.  Use your increased enthusiasm to advance yourself at work."},
  {"macne", "This is a good time for artists or performers who move during their activity.  There is increased creativity in movement.  This time could also involve secret actions behind the scenes."},
  {"macpl", "You have much heightened energy and will power.  This is a very important time for athletes and for all physical activities.  Drastic changes could be in store."},
  {"macsa", "Now you are driving the car with the breaks on.  Sometimes you can shoot ahead, but at other times you're grinding at a frustrating crawl.  This time can be favorable for business."},
  {"macur", "You have the urge to be impulsive.  Danger is exciting but try to avoid sudden crazy actions."},
  {"magju", "All your energy is under a favorable influence giving you confidence and enthusiasm.  Sports or exercise go well because you have extra courage and your actions are constructive."},
  {"magne", "This is a very good time for the energetic expression of creativity."},
  {"magpl", "You have great will power and powerful energy.  Business and all things that need hard work should go very well."},
  {"magsa", "This is a good time for steady progress through hard work.  Business matters call for extra effort but fruitful results are the reward."},
  {"magur", "Dynamic and unusual actions are favorable for you now.  Exciting adventures can come out well."},
  {"mebju", "Expansive influences can lead to an over-optimistic attitude.  You suffer from lack of attention to detail so you could end up promising more than you can deliver."},
  {"mebne", "You are subject at this time to false or impractical ideas.  Iron control is needed to avoid being deceived.  Double check any contracts you sign."},
  {"mebpl", "An overly forceful element can enter your thinking and speech during this time and cause quite some stress.  So hold your tongue and carefully check any contracts you get into."},
  {"mebsa", "A pessimistic attitude creates a vibration of failure and  sorrow.  Like attracts like.  Snap out of it and find a more positive outlook. You can be faced with a tremendous workload."},
  {"mebur", "Now you can feel restless, nervous or cranky.  Your mind is erratic and inconsistent.  This is not a great time to make important decisions since you can be too excitable and you can decide on an action which is too drastic and too sudden."},
  {"mecju", "This is an ideal time to press forward with mental activities.  Writing, studying, dealing with the media are favored.  Optimism is very high."},
  {"mecne", "You have an increased creative imagination, especially in the mental arts- music and literature.  Avoid misty-minded decisions."},
  {"mecpl", "This is the time when you're faced with big far-reaching decisions.  It's a good time for digging up facts."},
  {"mecsa", "You can find yourself shouldering many mental burdens, like  increased study loads or a heavy load at work.  There could be a tendency to be depressed, so you have to work hard to keep a positive attitude."},
  {"mecur", "You have original - maybe quirky - ideas and you have communication with lots of unusual and interesting people.  Be careful."},
  {"megju", "This is a good time to make mental advancements.  Apply your knowledge in a practical way.  Take courses.  Your optimistic attitude makes it easier to succeed."},
  {"megne", "You have an increased creative imagination.  It's a good time for meditation and study of higher things like philosophy or spiritual matters."},
  {"megpl", "This is an excellent time for making far-reaching decisions about insurance, loans and other people's money in general.  It's a good time for all business decisions."},
  {"megsa", "You have very good ability now to concentrate yourself mentally. It's a good time to make business decisions because you are more patient and disciplined.  It's good time for writing, teaching and learning."},
  {"megur", "It's a good time for a study of science, astrology and uncommon ideas."},
  {"mobju", "Expansion of your moods can lead to overindulgence in food.  Better to chain the fridge shut after dinner and go for a jog instead."},
  {"mobne", "During this period your moods are confused.  Try to control daydreaming or impractical ideas.  Avoid deception by keeping your feet solidly on the ground."},
  {"mobpl", "Your emotions are turned upside down by unavoidable pressures- especially in the home life."},
  {"mobsa", "Burdens in the home and family are at their height.  Business and home could be in conflict.  Your mood is low."},
  {"mobur", "Your moods are subject to big ups and downs at this time.  All kinds of unexpected changes and adjustments happen  around the home or the house."},
  {"mocju", "Harmony and optimism come into your home life.  This is a good time to have lots of dealings with women.  Avoid overeating."},
  {"mocne", "Intuition and creative imagination are highlighted.  Inward activities like meditation are benefited.  You're under very emotional influence now so you should attempt a more  practical, rational approach."},
  {"mocpl", "Increased emotional intensity makes the inevitable changes around the home at this time more difficult to handle.  You may deal with insurance, taxes and other matters involving money and the home and family."},
  {"mocsa", "You suffer delays and frustrations.  There could be a heavy sense of responsibility about things having to do with the home or your mother or the house."},
  {"mocur", "You have sudden changes of mood during this period, especially having to do with the home life.  You have unexpected changes at home."},
  {"mogju", "There is a peaceful, harmonizing influence in the home and it's a good time to make any changes in the house or home.  Dealings with the public are favorable."},
  {"mogne", "You're under good influences for increased imagination.  It's a good time for all creative people."},
  {"mogpl", "This is an excellent time to rejuvenate the existing conditions in the home life.  It's a good time to completely change your diet and exercise habits.  A mortgage could be easy to get."},
  {"mogsa", "Now's the time to set things right with your home and the house.  It's an excellent time to buy or sell a house or to do major renovations."},
  {"mogur", "A sudden favorable change of residence is possible.  You can deal with peculiar women at this time."},
  {"subju", "Expansion and optimism can be overdone and you are in danger of foolish optimism or extravagance."},
  {"subne", "There's a tendency to self-deception and to escape responsibility at this time.  You are in danger of being deceived or of deceiving others.  The fuzzy and misty atmosphere makes it difficult to muster the discipline and self-control needed for success."},
  {"subpl", "You can get involved in power struggles.  Do not throw your spouse out of the house because they again squeezed the toothpaste in the middle instead of the end."},
  {"subsa", "Frustration with delays and extra burdens affect you.  Little seems to go right.  Now is a great time for stress reduction.  Exercise. Meditation.  Never mind trying to fight overwhelming obstacles - go with the flow for awhile."},
  {"subur", "You are restless about current conditions and conventional ways of doing things.  There's a possibility that you can turn to unusual or even impractical projects. Beware of association with eccentric or unstable people at this time."},
  {"sucju", "You have expansive feelings and optimism.  This is a good time for travel or expanding your mind in some other way like special studies or religion."},
  {"sucne", "You have increased sensitivity and creative imagination at this time.  It's a interesting time for artists, musicians, show business folk and the like.  Be careful."},
  {"sucpl", "You have increased will power.  More self-assertion can  mean far-reaching changes in your life. Inexorable forces will shape your life."},
  {"sucsa", "You have an increased sense of responsibility.  You might find heavy burdens put on your shoulders.  Dealing with them well can bring you advancement, but be ready for some hard work."},
  {"sucur", "You under a strong impulse toward freedom in all your affairs.  Silly restrictions and boring routine drive you bananas. If you like surprises, then good, but this time can be seriously unsettled."},
  {"sugju", "You have expansive and optimistic influences in your favor. This is one of the best possible indicators and it brings all-round prosperity, progress and peace.  It's a good time to travel or start new projects."},
  {"sugne", "You have increased creativity and intuition.  It's an excellent time for the performing arts.  Romance at this time has an exotic flavor."},
  {"sugpl", "Your increased will power at this period makes it a good time to start an exercise program.  It's a good time to deal with loans, mortgages and other people's money in general."},
  {"sugsa", "This is a time for hard, steady work which brings good  results.  Business opportunities are excellent."},
  {"sugur", "You're in for exciting adventures which turn out well.  You have more popularity and unusual romantic episodes.  Creative expression is very original."},
  {"vebju", "You can be over-optimistic in love, or you could place your sympathy where it is not deserved.  This is a mild condition."},
  {"vebne", "This is the classic time for confusion in love.  People fall madly in love with people who lie, steal, cheat, kick dogs and generally aren't worth it.  Try hard to see the loved one as they  really are."},
  {"vebpl", "You have power struggles in the love life.  Beware of jealousy."},
  {"vebsa", "You are under the classic bad condition for matters of the heart.  Sorrow, delays and frustrations.  Never mind - you know when it ends."},
  {"vebur", "You have great ups and downs in the love department. There's a tendency to break bonds and conventions and to associate with unstable or irresponsible people. This same influence brings sudden and drastic breaks in love relationships."},
  {"vecju", "This is your time to shine.  Outstanding prospects in your love life are in store.  You have pleasant social affairs, meet lots of interesting people and have general good luck in the love department."},
  {"vecne", "This is a highly creative period for artists."},
  {"vecpl", "You have intense emotional experiences during this time.  Your attractiveness is much increased, so watch out!"},
  {"vecsa", "Your love life is going downhill.  It's a low key time. A consolidation can occur, however."},
  {"vecur", "Exciting new love interests show up.  Unexpected opportunities in the love department are the norm.  You deal with lots of people in groups and associations of all kinds.  It can be an unsettled time."},
  {"vegju", "Expansive qualities enhance your love life.  This is a period when you could be involved with more than one romantic involvement."},
  {"vegne", "This is an excellent time to have an ideal love interest enter your life.  You are under the best possible condition for creative activities.  Financial activities having to do with art or entertainment can be beneficial."},
  {"vegpl", "You have plenty of drive in creative activities.  The time is good for business dealings in art or entertainment.  You have very strong attractions in the romance department.   Money could unexpectedly fall into your lap."},
  {"vegsa", "This is a favorable time for slow steady progress in love and artistic matters."},
  {"vegur", "If you're artistic this is a time for very original creative discoveries.  You are very magnetic and can have favorable relations with unusual and brilliant people."}
};

#define NKEYS_ASP (sizeof f_asptab / sizeof(struct aspect))


/* end of futhtm.h */
