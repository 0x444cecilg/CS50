1. I am new to computer science and computer programming so I chose to create a simple imformation collective website
   involving blockchain technology and cryptocurrency. I used a lot of the fundemental concepts learned in the final week
   of the course as the information learned tended to tie everything together.

2. I choose Flask for my web framework, Python for my control along with SQL as my database. I used Javascript and CSS
   to create the interative background for the website. HTML along with JINJA was used to structure the website and CSS
   was used for some of the other design elements such as the glowing register link. As I left design to the very end,
   I had to hard code my dummy logo into each page that I wanted it to show up on, just seemed the fastest route. I used
   a bit of bootstrap, for the navigation bar located at the top of the site.

3. I used Python as my controlling backend language. Through my app.py you can see I tell the server the different routes
   to send the user based off of the choices made on the site. There lies the logic for if a user doesn't imput needed
   information, error checks and such. Also I have a helpers.py where I placed the login required function and imported
   from there into the app.py.

4. I created a static folder to hold the stylesheet and javascript in there respective folders. I crerated the templates
   folder to house all of the HTML files, the various webpages encountered throuout the site. In them you can see the various
   forms used for the user to interact with the site. The base.html file is the 'master' HTML file from which I used Jinja to
   extend its layout to the other pages allowing for quick fixes across many webpages at once.

5. I created 2 tables using SQLlite. One for the users registering to the website, storing their user id, username and
   password. A second table was created to store the first/last names and emails of users that subscribe to our newsletter.

6. Users are able to register, giving them access to the site through a login. Users can change their password.
   Users can subscribe to a newsletter which gives an email alert to both myself and the user. Users can browse through
   various pages that give information on blockchain tachnology and different aspects of the field with video and links,
   and users can logout returning them to the login page.
