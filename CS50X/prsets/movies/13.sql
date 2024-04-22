SELECT DISTINCT people.name
FROM people, stars, movies
WHERE people.id = stars.person_id
  AND stars.movie_id = movies.id
  AND movies.id IN (
    SELECT movie_id
    FROM stars, people
    WHERE stars.person_id = people.id
      AND people.name = 'Kevin Bacon'
      AND people.birth = 1958
  )
  AND people.name <> 'Kevin Bacon';
