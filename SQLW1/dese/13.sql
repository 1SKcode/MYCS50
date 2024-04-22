SELECT
    districts.name,
    districts.state,
    expenditures.per_pupil_expenditure,
    staff_evaluations.exemplary
FROM districts
INNER JOIN expenditures ON expenditures.district_id = districts.id
INNER JOIN staff_evaluations ON staff_evaluations.district_id = districts.id
WHERE staff_evaluations.exemplary > (
    SELECT AVG(exemplary)
    FROM staff_evaluations
)
AND expenditures.per_pupil_expenditure < (
    SELECT AVG(per_pupil_expenditure)
    FROM expenditures
);
